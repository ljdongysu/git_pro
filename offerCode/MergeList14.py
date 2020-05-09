# -*- coding:utf-8 -*-
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None
class Solution:
    def MergeListNode(self,pHead1,pHead2):
        resultHead = ListNode(0)
        result = resultHead

        while pHead1 != None and pHead2 != None:
            if (pHead1.val < pHead2.val):
                resultHead.next = pHead1.next
                pHead1 = pHead1.next
            else:
                resultHead.next = pHead2.next
                pHead2 = pHead2.next
            resultHead = resultHead.next
        if pHead1 != None:
            resultHead.next = pHead1
        if pHead2 != None:
            resultHead.next = pHead2
        return result.next


