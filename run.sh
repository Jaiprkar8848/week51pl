output_file="memtim.txt"
echo "Mem(in KB),Time(in s)" > $output_file

N=10

for M in {1..8}; 
do
    g++ -DN=$N -DM=$M 1.cpp -o 1
    /usr/bin/time -v ./1  < file1.txt 2> log.txt
    tim=$(grep "Elapsed (wall clock) time" log.txt | awk '{printf $8}')
    echo "$M,$tim" >> $output_file
done