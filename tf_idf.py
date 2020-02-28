from math import log
import pandas as pd
import numpy as np
 
docs = [
    ["t1","t3","t3","t3","t4","t4","t4","t4","t4","t4","t5","t5","t5","t5"],
    ["t2","t2","t2","t3","t3","t4","t4","t4","t4","t4","t4","t5","t6","t6","t6","t6","t6"],
    ["t1","t1","t1","t1","t1","t4","t4","t4","t4","t4","t4","t4","t4","t5","t5","t5","t5"],
    ["t1","t1","t3","t3","t3","t3","t4","t4","t4","t4","t4","t4","t4","t6","t6","t6"],
    ["t1","t1","t1","t4","t4","t4","t4","t4"]
]
 
words = list(set(w for doc in docs for w in doc))
words.sort()
words

N = len(docs)
 
def tf(t, d):
    return d.count(t)/len(d)
 
def idf(t):
    df = 0
    for doc in docs:
        df += t in doc
    
    return log(N/df)+1
 
def tfidf(t, d):
    return tf(t,d)* idf(t)

result = []
for i in range(N):
    result.append([])
    d = docs[i]
    for j in range(len(words)):
        t = words[j]
        
        result[-1].append(tf(t,d))
        
tf_ = pd.DataFrame(result, columns=words)
tf_

result = []
for j in range(len(words)):
    t = words[j]
    result.append(idf(t))

idf_ = pd.DataFrame(result, index=words, columns=["IDF"])
idf

result = []
for i in range(N):
    result.append([])
    d = docs[i]
    for j in range(len(words)):
        t = words[j]
        
        result[-1].append(tfidf(t,d))

        tfidf_ = pd.DataFrame(result, columns=words)
tfidf

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.metrics.pairwise import cosine_similarity
transformer = TfidfTransformer()
vectorizer = TfidfVectorizer(token_pattern=u'(?u)\\b\\w+\\b')
docs=["t1 t3 t3 t3 t4 t4 t4 t4 t4 t4 t5 t5 t5 t5 t5",
      "t2 t2 t2 t3 t3 t4 t4 t4 t4 t4 t4 t5 t6 t6 t6 t6 t6",
      "t1 t1 t1 t1 t1 t4 t4 t4 t4 t4 t4 t4 t4 t5 t5 t5 t5",
      "t1 t1 t3 t3 t3 t3 t4 t4 t4 t4 t4 t4 t4 t6 t6 t6",
      "t1 t1 t1 t4 t4 t4 t4 t4"]

test=["t2 t3 t4"]

docs_np = np.array(docs)
test_np = np.array(test)
tf = vectorizer.fit_transform(docs_np)
tf2 = vectorizer.transform(test_np)
tfidf = transformer.fit_transform(tf) # 各ドキュメントのtfidfを計算
test_tfidf = transformer.fit_transform(tf2)# testドキュメントのtfidfを計算

similarity = cosine_similarity(test_tfidf, tfidf)[0] 
topn_indices = np.argsort(similarity)[::-1][:3]
print(topn_indices)
