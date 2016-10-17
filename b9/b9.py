from  math import log
from math import sqrt
from collections import Counter
from operator import itemgetter

def idf(term,allDocuments):
	numofdocwiththisterm=0
	for doc in allDocuments:
		for word in doc:
			numofdocwiththisterm=numofdocwiththisterm+1
	if numofdocwiththisterm >0:
		return round(log(float(float(len(allDocuments))/float(numofdocwiththisterm)),2),3)
	else:
		return 0

def tf(term,document):
	return document.count(term)

def tfidf(term,doc):
	return tf(term,doc)*idf(term,terms)

def cosine_similarity(doc,q,d):
	a=0
	for x in d:
		a=a+tfidf(x,doc)*tfidf(x,q)
	b=lengthof(doc,d)*lengthof(q,d)

	if not b:
		return 0
	else:
		return round(a/b,3)
def lengthof(doc,d):
	val=0
	for x in d:
		val=val+pow(tfidf(x,doc),2)
	return sqrt(val)

f=[]
doc=['doc1.txt','doc2.txt','doc3.txt','doc4.txt','doc5.txt','doc6.txt']
dataset=[['doc1.txt','science'],['doc2.txt','science'],['doc3.txt','science'],['doc4.txt','entertainment'],['doc5.txt','entertainment'],['doc6.txt','entertainment']]

for x in doc:
	f.append(open(x,'r').read())

testf=raw_input('test file>>>>')
q=open(testf,'r').readline().lower()

terms=[]

for x in f:
	terms.append(x.lower().rstrip('\n'))

fin_terms=[]
for x in terms:
	fin_terms=fin_terms+x.split()
fin_terms=set(fin_terms)
fin_terms=list(fin_terms)

cnt=0
for x in terms:
	dataset[cnt]=dataset[cnt]+[cosine_similarity(x,q,fin_terms)]	
	cnt=cnt+1
print dataset

k=3

sorted_dataset=sorted(dataset,key=itemgetter(2),reverse=True)
top_k=sorted_dataset[:k]

top_k[:]=(x for x in top_k if x[2]!=0)
print top_k

if len(top_k) == 0:
	print "no match"
else:
	class_counts=Counter(category for(document,category,value) in top_k)
	classification=max(class_counts ,key= lambda cls :class_counts[cls])
	print classification
