#不可变（immutable）：int、字符串(string)、float、（数值型number）、元组（tuple)，None
# 可变（mutable）变量：字典型(dictionary)、列表型(list)
# -*- coding:utf-8 -*-

#  Variable type ,可变变量c赋值给其他变量d时候，然后源变量单个元素改变时候,c,d同时改变，但是若c整体改变，则d不变
# 注意ReverseList3函数中            tmp = cur.next    cur.next = pre 与整体改变相对应，若tmp=cur的化，cur.next变化，tmp也会随之改变
def VariableType():
    a = ListNode(10)
    b = a
    a.val = 5
    print(a.val,b.val)

    c = [1,2,3]
    d = c
    c[1] = 0
    print(c,d)
    c = [4,5,6]
    print(c,d)
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def ReverseList(self, pHead):

        if pHead.next == None:
            return pHead

        new_next = ListNode(pHead.val)
        new_current = new_next
        while pHead.next is not None:
            pHead = pHead.next
            new_next = ListNode(pHead.val)
            new_next.next = new_current
            new_current = new_next
        return new_current

    def ReverseList1(self, pHead):

        if pHead.next == None or pHead == None:
            return pHead

        pre = None
        new_current = pHead
        new_current.next = pre
        pre = new_current
        while pHead != None:
            pHead = pHead.next
            new_current = pHead
            new_current.next = pre
            pre = new_current
        return new_current

    def ReverseList3(self, pHead):
        # write code here
        if pHead == None or pHead.next == None:
            return pHead
        pre = None
        cur = pHead
        while cur:
            tmp = cur.next
            cur.next = pre
            pre = cur
            cur = tmp
        print(pHead.next)
        return pre
def valListNode():
    a = ListNode(0)
    b = ListNode(1)
    a.next = b
    c = a.next
    d = a
    a.next = ListNode(10)
    print(a.next.val,b.val,c.val,d.next.val)
def main():
    a = ListNode(0)
    phead = a
    for i in range(1,10):
        a.next = ListNode(i)
        a = a.next

    # while phead:
    #     print(phead.val)
    #     phead = phead.next

    b = Solution()
    c = b.ReverseList3(phead)

    while c:
        print(c.val)
        c = c.next
if __name__ == '__main__':
    main()