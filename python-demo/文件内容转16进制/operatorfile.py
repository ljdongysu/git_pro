def write_file(newfilecpp,middle_str):
    newfile = "#include <string>\nstd::string m_ptx_source = {" + middle_str + "};"
    with open(newfilecpp,'w') as f:
        f.write(newfile)
def get_x16(filecu):
    with open(filecu,'r') as f:
        file = f.read()
    print("file length: ",len(file))
    x16 = str_to_hex(file)
    # print(x16)
    print("x16 length: ",len(x16))
    # print(remove)
    x16_4bit = x16_limit_to_4bit(x16)

    print(len(''.join(x16_4bit.split(','))))

    print("file 4 length: ",len(file)*4)
    return x16_4bit


def str_to_hex(s):
    return ','.join([hex(ord(c)) for c in s])

def x16_limit_to_4bit(x16_str):
    x16_4bit = x16_str.split(',')
    sub_length = 0
    dot_length = 0
    for i in range(len(x16_4bit)):
        if len(x16_4bit[i]) ==4:
            continue
        elif len(x16_4bit[i]) == 3:
            dot_length += 1
            temp = x16_4bit[i][:2] + '0' + x16_4bit[i][2]
            x16_4bit[i] = temp
        elif len(x16_4bit[i]) == 5:
            sub_length +=1
            continue
        else:
            print(len(x16_4bit[i]))
            assert 0
        # print(i,x16_4bit)
    print(sub_length)
    print(len(x16_4bit))
    print(len(x16_str),len(''.join(x16_4bit))-dot_length)
    assert (len(x16_str) == len(''.join(x16_4bit)) - dot_length)

    x16_4bit = ','.join(x16_4bit)
    x16_4bit = str.upper(x16_4bit)
    x16_4bit = x16_4bit.replace('X','x')
    return x16_4bit
def main():
    write_file_name = "/home/ljdong/chang2binary/vectorAdd_kernelP.cpp"
    filecu = "/home/ljdong/chang2binary/vectorAdd_kernel.cu"
    x16_4bit = get_x16(filecu)
    write_file(write_file_name,x16_4bit)
if __name__ == '__main__':
    main()





