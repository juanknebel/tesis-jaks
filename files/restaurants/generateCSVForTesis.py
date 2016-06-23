import mysql.connector
import sys

cities = "cities"
restaurants = "restaurants"
kitchen = "kitchen"
restaurantKitchenType = "restaurant_kitchen"
similarity = "similarity"
hostName = "localhost"
userDb = "root"
paswdDb = "passw0rd"
dbName = "restaurants"
nodeName = "node_name.csv"
nodeCost = "node_cost.csv"
nodeCompatibility = "node_compatibility.csv"
typeName = "type_name.csv"
nodeCover = "node_cover.csv"
separator = "\t"
endOfLine = "\n"

def generateNodeName(cityId):
	db = mysql.connector.connect(host=hostName, user=userDb, passwd=paswdDb, db=dbName)
	sql = "select id,name from " + restaurants +" where city=" + str(cityId) + " order by 1 asc"
	cursor = db.cursor()
	cursor.execute(sql)
	fileNodeName = open(nodeName,"w")
	for (id, name) in cursor:
		fileNodeName.write(str(id) + separator + name + endOfLine)
	db.close()
	fileNodeName.close()
	
def generateNodeCost(cityId):
	db = mysql.connector.connect(host=hostName, user=userDb, passwd=paswdDb, db=dbName)
	sql = "select id,cost from " + restaurants + " where city=" + str(cityId) + " order by 1 asc"
	cursor = db.cursor()
	cursor.execute(sql)
	fileNodeCost = open(nodeCost,"w")
	for (id,cost) in cursor:
		fileNodeCost.write(str(id) + separator + str(cost) + endOfLine)
	db.close()
	fileNodeCost.close()
	
def generateNodeCompatibility(cityId):
	db = mysql.connector.connect(host=hostName, user=userDb, passwd=paswdDb, db=dbName)
	sql = "select s.restaurant1,s.restaurant2,s.inter from " + similarity + " s, " + restaurants + " r, " + restaurants + " re where s.restaurant1=r.id and s.restaurant2=re.id and r.city=re.city and r.city=" + str(cityId) + " order by 1 asc"
	cursor = db.cursor()
	cursor.execute(sql)
	fileNodeCompatibility = open(nodeCompatibility, "w")
	for (rest1,rest2,jaccard) in cursor:
		fileNodeCompatibility.write(str(rest1) + separator + str(rest2) + separator + str(jaccard) + endOfLine)
	db.close()
	fileNodeCompatibility.close()
	
def generateTypeName(cityId):
	db = mysql.connector.connect(host=hostName, user=userDb, passwd=paswdDb, db=dbName)
	sql = "select id,name from " + kitchen + " order by id asc"
	cursor = db.cursor()
	cursor.execute(sql)
	fileTypeName = open(typeName, "w")
	for (id,name) in cursor:
		fileTypeName.write(str(id) + separator + name + endOfLine)
	db.close()
	fileTypeName.close()
	
def generateNodeCover(cityId):
	db = mysql.connector.connect(host=hostName, user=userDb, passwd=paswdDb, db=dbName)
	sql = "select rk.restaurant,rk.kitchen from " + restaurantKitchenType + " rk, " + restaurants + " r where rk.restaurant=r.id and r.city=" + str(cityId) + " order by rk.restaurant asc"
	cursor = db.cursor()
	cursor.execute(sql)
	coverMap = {}
	for (rest,kitchen) in cursor:
		if rest in coverMap.keys():
			coverMap[rest] = coverMap[rest] + [kitchen]
		else:
			coverMap[rest] = [kitchen]
	db.close()
	fileNodeCover = open(nodeCover,"w")
	
	for rest,kitchens in coverMap.items():
		fileNodeCover.write(str(rest))
		for kit in kitchens:
			fileNodeCover.write(separator + str(kit))
		fileNodeCover.write(endOfLine)
	fileNodeCover.close()
	
def checkCityId(cityId):
	db = mysql.connector.connect(host=hostName, user=userDb, passwd=paswdDb, db=dbName)
	sql = "select id from " + cities + " where id=" + str(cityId)
	cursor = db.cursor()
	cursor.execute(sql)
	data = cursor.fetchone()
	db.close()
	return (data!=None)

election = sys.argv[1]
if election == "-c":
	cityId = int(sys.argv[2])
	exists = checkCityId(cityId)
	if (not exists):
		print ("Ciudad con id: " + str(cityId) + " inexistente")
	else:
		generateNodeName(cityId)
		generateNodeCost(cityId)
		generateNodeCompatibility(cityId)
		generateTypeName(cityId)
		generateNodeCover(cityId)
else:
	print("Error. Modo de ejecucion: \n" + sys.argv[0] + " -c idCiudad")
