import os
import shutil

#get  full file name list for dir
def get_fullname_list(file_name):
    fullname_list = []
    for root,dir,files in os.walk(file_name):
        for file in files:
            fullname_list.append(os.path.join(root,file))
    return fullname_list
def get_same_name(fullname_list,namefiletxt):
    file_need_remove = []
    with open(namefiletxt,'r')  as f:
        file_name = f.read()
    file_name_lit = file_name.split()
    for file1 in fullname_list:
        for file2 in file_name_lit:
            if file1.split('/')[-1] == file2.split('/')[-1]:
                file_need_remove.append(file1)
    print(len(file_need_remove))
    for i in file_need_remove:
        print(i)
        if os.path.exists(i):
            os.remove(i)
# move file of file  very dir name file
def dev_file_folder(file_list):
    folder_list = []
    for i in file_list:
        folder = i.split('.')[0]
        if folder not in folder_list:
            folder_list.append(folder)
            print(folder)
            os.mkdir(folder)
            shutil.move(i,folder+'/' + i.split('/')[-1])
        else:
            print("has : ",folder)
            shutil.move(i,folder+'/' + i.split('/')[-1])


if __name__ == '__main__':
    file_name = "/home/ljdong/data/dna_data/视频版权检测算法/train-35/1659111900"
    fullname_list = get_fullname_list(file_name)
    print(fullname_list)

    with open("/home/ljdong/无标题文档3",'w') as f:
        for i in fullname_list:
            f.write(i)
            f.write('\n')
    # dev_file_folder(fullname_list)
