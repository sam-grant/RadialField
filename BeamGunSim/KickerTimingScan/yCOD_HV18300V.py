import pandas as pd
import numpy as np
from ROOT import TFile, TGraph, TH1D, TCanvas
from array import array

file = 'yCOD_HV18300V.txt'
data = pd.read_csv(file, sep='\t')#,header=None)

#data = pd.to_numeric(data, downcast='float')
#print(data)
#print(data["Angle[deg]"])
#data["Angle[deg]"] = pd.to_numeric(data["Angle[deg]"], downcast="float")

print(data)

# Load columns in a list
yPos = data['<y>[m]'].tolist()
theta = data['Angle[deg]'].tolist()
n = len(theta)

x, y = array('f'), array('f')

for i in range(n):
    if(theta[i]=='<y>[m]' or theta[i]=='Angle[deg]'): continue
    x.append(float(theta[i]))
    y.append(float(yPos[i]))



gr = TGraph(n,x,y)

c = TCanvas("c","c",800,600)
gr.Draw("AP")
c.SaveAs("test.png")
#print(theta)
#data = data[data['<y>[m]']
#print(data[data['<y>[m]'])
