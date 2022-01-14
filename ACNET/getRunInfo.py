import psycopg2 # postgreSQL interface
import os
from datetime import timedelta
import glob

# Query the online postgres database to get the time of the run.
def getRunTimesFromDB(dbase,user,host,port,runMin,runMax):

    runTimes = {}
    qualityFlags = {}
    psqlConnect = "dbname=%s user=%s host=%s port=%d" % (dbase,user,host,port)
    db = psycopg2.connect(psqlConnect)
    DBconn = db.cursor()
    # escape the quotes since a complete clown created an SQL table with a column name that has spaces in it..
    sql_str = 'select \"Start time\", quality, \"Run number\" from runlog where \"Run number\" >= %d and \"Run number\" <= %d order by \"Run number\" ASC'  % (runMin,runMax)
    #print "Querying online database: %s" % (sql_str)
    try:
        DBconn.execute(sql_str)
        db.commit()
        if (DBconn.rowcount < 1):
            print "ERROR: SQL(): getRunTimesFromDB() returned no rows"
        else:    
            rows = DBconn.fetchall()
            for row in rows:
                dt = row[0]
                qual = row[1]
                run = int(row[2])
                qualityFlags[run] = qual
                runTimes[run] = dt
    except:
        print "SQL(): executeSQL: error"
        db.rollback()
        
    return runTimes, qualityFlags

def getReadingFromDB(dbase,user,host,port,runTime,sensor):

    # Set range of times for this temperature (+/- 30 secs from run) wider for acnet
    runTimeLow = runTime - timedelta(seconds=150)
    runTimeHigh = runTime + timedelta(seconds=150)
    runTemp = -1
    psqlConnect = "dbname=%s user=%s host=%s port=%d" % (dbase,user,host,port)
    db = psycopg2.connect(psqlConnect)
    DBconn = db.cursor()
    # mscb13e_Temp_P2 corresponds to MAGNET TEMP BETWEEN SECTORS F & H
    sql_str = 'SELECT value FROM g2sc_values WHERE channel = \''+sensor+'\' AND time > \'%s\' AND time < \'%s\' LIMIT 1' % (runTimeLow, runTimeHigh);
   # print "Querying online database: %s" % (sql_str)
    try:
        DBconn.execute(sql_str)
        db.commit()
        if (DBconn.rowcount < 1):
            print "ERROR: SQL(): getReadingFromDB() returned no rows " + sensor
        else:    
            rows = DBconn.fetchall()
            for row in rows:
                values = row[0]
                totalVal = 0
                nVal = 0
                for val in values :
                  if val > 0 :
                    totalVal = totalVal + val
                    nVal = nVal + 1
                runTemp = totalVal/nVal
    except:
        print "SQL(): executeSQL: error"
        db.rollback()
        
    return runTemp


# Return dictionary with key of run-number and value which is the run time in datatime format
# Need a .pgpass file with usernames and passwords and can connect to localhost or ifdbprod.fnal.gov
# localhost is via a ssh proxy to the online DB e.g.
# "ssh -L 5434:192.168.30.51:5433 gmgateway -N" or similar
# or you are in FNAL and can then connect to ifdbprod.fnal.gov

# --> localhost via proxy connect (eg outside FNAL)
#runTimes = getRunTimesFromDB('gm2_online_prod','gm2_reader','localhost',5434,runMin,runMax)

# --> ifdbprod i.e. replicated online database that is available without proxy but has short timelag on contents
runMin=16355
runMax=16539
#runMax=16355
print "Get run times:"
runTimes, qualityFlags = getRunTimesFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runMin,runMax)
# e.g. time = runTimes[7438]
print "done."

for run in sorted(qualityFlags.iterkeys()):
  if qualityFlags[run] == 'Y' :
    acnetTemp = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'acnet_weather_gtemp')
    acnetDTemp = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'acnet_weather_dtemp')
    acnetPress = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'acnet_weather_gbpress')
    acnetHumid = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'acnet_weather_ghumid')


    temp1 = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'mscb13e_Temp_P2')
    temp2 = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'mscb174_Temp_P1')
    temp3 = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'mscb323_Temp_P1')
#    temp4 = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'mscb319_PT1000_P5')
    
    ADC = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'mscb174_ADC_P0')
    ADC2 = getReadingFromDB('gm2_online_prod','gm2_reader','ifdbprod.fnal.gov',5452,runTimes[run], 'mscb13e_ADC_P0')
    
    print run, runTimes[run].year, runTimes[run].month, runTimes[run].day, runTimes[run].hour, runTimes[run].minute, runTimes[run].second, ("%.2f" % acnetTemp), ("%.2f" % acnetDTemp), acnetPress, acnetHumid, ("%.2f" % temp1), ("%.2f" % temp2), ("%.2f" % temp3), ("%.2f" % ADC), ("%.2f" % ADC2)
