import csv
import os
dirs = os.listdir('/home/ljdong/data/dna_data/视频版权检测算法/refer')
print(dirs)
list = [i.split('.')[0] for i in dirs]
print(list)


f = open('test.csv','w')
f_csv = csv.writer(f)




with open('train.csv','r') as f1:
    reader = csv.reader(f1)
    print(type(reader))
    i = 0
    for row in reader:
        if row[2] in list:
            f_csv.writerow(row)
        else:
            continue
f.close()





