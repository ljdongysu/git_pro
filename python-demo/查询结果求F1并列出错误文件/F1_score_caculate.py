import csv

def getCalss(file_path):
    file_path = file_path.split('/')
    return file_path[-2]
def get_TP(query_label, refer_list, similarity_list, similarity):
    TP = 0
    FP1 = 0
    FP2 = 0
    FN = 0
    TN = 0
    query_result = []
    for i in range(len(query_label)):
        if similarity <= float(similarity_list[i]):
            query_result.append(refer_list[i])
        else:
            query_result.append(None)
    for i in range(len(query_label)):
        # 标签为空，视频标签没有侵权
        if query_label[i] is None:
            #预测为没有侵权
            if query_result[i] is None:
               TN += 1
            #预测为侵权
            else:
                FP1 += 1
        #标签侵权
        else:
            #预测正确
            if query_label[i] == query_result[i]:
                TP += 1
            # 预测错误
            else:
                # 预测为空
                if query_result[i] is None:
                    FN += 1
                # 预测为错误标签
                else:
                    FP2 += 1

    FP = FP1 + FP2
    TPR = TP/(TP+FP)
    FPR = TP/(TP+FN)
    F1 = 2*TP/(2*TP + FP +FN)
    return TPR, FPR, F1,(TP+TN)/(TP+TN+FN+FP), TP, TN,FN,FP, FP1,FP2

#获取入库标签，查询标签，入库文件列表，查询文件列表，相似度列表
def refer_query_similarity(file_scv):
    count = 0
    with open(file_scv, 'r') as f:
        reader = csv.reader(f)
        print(type(reader))
        refer_list = []
        query_list = []
        result_file_list = []
        query_file_list = []
        similarity_list = []
        for row in reader:
            # print(row)
            if (count ==0):
                count += 1
                continue
            refer_list.append(getCalss(row[0]))
            query_list.append(getCalss(row[1]))
            result_file_list.append(row[0])
            query_file_list.append(row[1])
            similarity_list.append(row[2])
    return refer_list, query_list, result_file_list, query_file_list, similarity_list

 #获取查询视频真实标签（视频路径次级文件夹名称）
def test_null(query_file, refer_file):
    with open(refer_file,'r') as f:
        file_r = f.read()
    with open(query_file,'r') as f:
        file_q = f.read()
    refer_class = []
    # print(len(file_r.split()))
    for file in file_r.split():
        # print(0,file)
        if getCalss(file) in refer_class:
            continue
        else:
            refer_class.append(getCalss(file))
    query_label = []
    label_file_list = []
    for file in file_q.split():
        if getCalss(file) in refer_class:
            query_label.append(getCalss(file))
            label_file_list.append(file)
        else:
            query_label.append(None)
            label_file_list.append(None)
    return query_label, label_file_list
def wrong_file_information(query_label, refer_list, similarity_list, similarity,result_file_list, query_file_list,label_file_list ):
    query_result = []
    with open('/home/ljdong/data/similarity_wrong0.csv', 'w') as f:
        writer = csv.writer(f)
        for i in range(len(query_label)):
            if similarity <= float(similarity_list[i]):
                query_result.append(refer_list[i])
            else:
                query_result.append(None)
                result_file_list[i] = None
        writer.writerow(["query_file","result_file","lable_file","wrong_class","similarity="+str(similarity_list)])
        for i in range(len(query_label)):
            # 标签为空，视频标签没有侵权
            if query_label[i] is None:
                # 预测为没有侵权
                if query_result[i] is None:
                    #TN += 1
                    pass
                # 预测为侵权
                else:
                    #FP1 += 1
                    writer.writerow([query_file_list[i],result_file_list[i],  label_file_list[i], "FP1"])
            # 标签侵权
            else:
                # 预测正确
                if query_label[i] == query_result[i]:
                    # TP += 1
                    pass
                # 预测错误
                else:
                    # 预测为空
                    if query_result[i] is None:
                        # FN += 1
                        writer.writerow([query_file_list[i], result_file_list[i], label_file_list[i], "FN"])
                    # 预测为错误标签
                    else:
                        writer.writerow([query_file_list[i], result_file_list[i], label_file_list[i], "FP2"])
                        # FP2 += 1
#获取最大F1对应的相似度阈值
def getMaxSimilarity(query_label, refer_list, similarity_list):
    i = 0
    T = []
    R = []
    F1 = []
    ACC =[]
    similarity_increase = []
    while (i <= 1):
        t, r, f1, acc,TP, TN,FN,FP, FP1,FP2 = get_TP(query_label, refer_list, similarity_list, i)
        T.append(t)
        R.append(r)
        F1.append(f1)
        ACC.append(acc)
        similarity_increase.append(i)
        i += 0.001
        print("i: ", i, "TP, TN,FN,FP, FP1,FP2: ", TP, TN, FN, FP, FP1, FP2)
        if (i >= 0.497):
            break
    print("TPR: ",max(T), T.index(max(T)), T[F1.index(max(F1))])
    print("FPR: ", max(R), R.index(max(R)),R[F1.index(max(F1))])
    print("RECALL: ",)
    print("F1: ",max(F1),similarity_increase[F1.index(max(F1))])
    print("ACC: ", max(ACC),similarity_increase[ACC.index(max(ACC))],ACC[F1.index(max(F1))])
    return similarity_increase[ACC.index(max(ACC))]
if __name__ == '__main__':
    #查询视频列表文件
    query_video_file = "/home/ljdong/data/dna_data/视频版权检测算法/NDVR/query_aiqiyi.txt"
    #入库视频列表文件
    refer_video_file = "/home/ljdong/data/dna_data/视频版权检测算法/NDVR/store_aiqiyi.txt"
    #获取查询视频真实标签（视频路径次级文件夹名称）
    query_label, label_file_list = test_null(query_video_file,refer_video_file)

    # csv文件，存储查询结果，查询视频，similarity和时间
    file_csv = '/home/ljdong/data/similarity.csv'
    #获取入库标签，查询标签，入库文件列表，查询文件列表，相似度列表
    refer_list, query_list, result_file_list, query_file_list, similarity_list = refer_query_similarity(file_csv)
    #获取最大F1对应的相似度阈值
    similarityMax = getMaxSimilarity(query_label, refer_list, similarity_list)
    #将错误查询视频对应查询视频列表，入库视频列表和查询视频对应的真实标签视频和错误类型写入csv文件
    wrong_file_information(query_label, refer_list, similarity_list, 0, result_file_list, query_file_list, label_file_list)





