i=2
rm -f run${i}.txt && touch run${i}.txt
comm -23 <(sort ../CaloRunNumbers/run${i}.txt) <(sort ../CurrentRunNumbers/run${i}.txt) >> run${i}.txt

