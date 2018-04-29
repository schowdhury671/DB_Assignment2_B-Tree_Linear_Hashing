import sys

class HashTable(object):
	def __init__(self,n,B):
		self._size = n
		self._N = self._size
		self._b=B
        	self._ht = []
		
        	for i in range (1,self._size+1):
			self._bucket = Bucket(self._b)
			self._ht.append(self._bucket)
		self._collision = 0
		self._total = 0
		self._loadFactor = 1.5

	def find(self,element):
		s = len(self._ht)
		product = 1
		while product<s:
			product *= 2
        	temp = element%product
		if(temp >= s):
            		return temp-self._size;
        	else:
            		return temp;

	def calculateLoad(self):
		return self._total / len(self._ht)

	def split(self):
		bucket = Bucket(self._b)
		self._ht.append(bucket)	
		if(self._collision % (self._N/2)==0):
           		 self._N=2*self._N;
        	self._ht[len(self._ht)-self._size-1].split(bucket,2*self._size,len(self._ht)-1);
        	
		

	def insert(self,element):
		position = self.find(element)
		#print position
		if element in self._ht[position]._elements:
			return
		self._ht[position].insert(element)	
		self._total = self._total + 1
		#if(self._ht[position].getCurrentSize()>self._b):
		if (self.calculateLoad() > self._loadFactor):
			self.split()
			self._collision = self._collision + 1
			if (self._collision == self._size):
				self._size *= 2
				self._collision = 0
		#self.display()
		#print "inserted "+str(element)
		return element
	
	def display(self):
		for i in self._ht:
			for j in i._elements:
				print j,
			print "\n",
		print "\n",

	
	
class Bucket(object):
	def __init__(self,n):
		self._b = n
		self._currentSize = 0
		self._elements = []
	def insert(self,element):
		self._elements.append(element)
		self._currentSize = self._currentSize + 1

	def split(self, bucket, div, targetpos):
		splitted = []
		#print self._elements
		for i in self._elements:
			#print "in"
			if i % div == targetpos:
				bucket._elements.append(i)
				node = 2
				#print node
				splitted.append(i)
				node = 3
				#print node	 
				self._currentSize = self._currentSize - 1
		self._elements = [x for x in self._elements if x not in splitted]

	def getCurrentSize(self):
		return self._currentSize

filename = sys.argv[1]
M = int(sys.argv[2])
B = int(sys.argv[3])
ht = HashTable(2,B/4)		
f = open(filename, "r")
ibuff = []
obuff = []
for line in f:
	ibuff.append(int(line.rstrip()))
	if (len(ibuff) == ((M-1)*B)/4):
			while ibuff:
				e = ibuff[0]	
				del ibuff[0]
				op = ht.insert(e)
				
				if (len(obuff) < (B/4)) and (op is not None):
					obuff.append(op)	
				else:
					while obuff:
						print obuff[0]	
						del obuff[0]
					if op is not None:
						obuff.append(op)		

	while ibuff:
			e = ibuff[0]	
			del ibuff[0]
			op = ht.insert(e)
			if (len(obuff) < (B/4)) and (op is not None):
				obuff.append(op)	
			else:
				while obuff:
					print obuff[0]	
					del obuff[0]
				if op is not None:
					obuff.append(op)		
	while obuff:
			print obuff[0]	
			del obuff[0]
#print "The hashtable:"
#ht.display()
