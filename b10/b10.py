from itertools import chain,combinations
from collections import defaultdict

import os

def getTranscationList(data_iterator):
	transactionList=list()
	itemSet=set()
	for record in data_iterator:
		transaction=frozenset(record)
		transactionList.append(transaction)
		for item in transaction:
			itemSet.add(frozenset([item]))

	return itemSet,transactionList


def joinset(itemSet,length):
	return set([i.union(j) for i in itemSet for j in itemSet if len(i.union(j))==length])

def returnItemsWithMinSupport(itemSet,transactionList,minSupport,freqSet):
	_itemSet=set()
	localSet=defaultdict(int)

	for item in itemSet:
		for transaction in transactionList:
			if item.issubset(transaction):
				freqSet[item]+=1
				localSet[item]+=1
	for item,count in localSet.items():
		suppport=float(count)/len(transactionList)
		if suppport >=minSupport:
			_itemSet.add(item)

	return _itemSet

def dataFromFile(fname):
	file_iter=open(fname,'rU')
	for line in file_iter:
		line=line.strip().rstrip(',')
		record=frozenset(line.split(','))
		yield record

def printResult(items):
	max_length=0
	print "\n"

	for item,support in sorted(items,key=lambda (item,support): support):
		if len(item)>=max_length:
			max_length=len(item)
	print "The frequent itemset extracted with Apriori Algorithm with min support count as 3 (relative support as 0.6) is:\n"

	for item,support in sorted(items,key=lambda (item,support): support):
		if len(item) == max_length:
			print "item: %s" % str(item)



def runApriori(data_iterator,minSupport):

	itemSet,transactionList=getTranscationList(data_iterator)

	freqSet=defaultdict(int)
	largeSet=dict()

	oneCSet=returnItemsWithMinSupport(itemSet,transactionList,minSupport,freqSet)

	print "L1"

	currentLSet=oneCSet
	print currentLSet

	k=2

	while(currentLSet != set([])):
		largeSet[k-1]=currentLSet
		currentLSet=joinset(currentLSet,k)

		print"\n"
		print "L",k

		print currentLSet
		currentCSet=returnItemsWithMinSupport(currentLSet,transactionList,minSupport,freqSet)

		currentLSet=currentCSet

		k=k+1
		def support(item):
			return float(freqSet[item]/len(transactionList))

		toReItems=[]

		for key,value in largeSet.items():
			toReItems.extend([(tuple(item),support(item)) for item in value	])

		return toReItems

if __name__ == "__main__":

	inFile=None
	inFile=dataFromFile("dataset.csv")
	minSupport=0.6
	items=runApriori(inFile,0.6)
	printResult(items)