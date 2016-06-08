import mysql.connector

cities = "cities"
restaurants = "restaurants"
kitchen = "kitchen"
restaurantKitchenType = "restaurant_kitchen"
similarity = "similarity"

def insertCities():
	db = mysql.connector.connect(host="localhost", user="tesis", passwd="tesis", db="tesis_restauratns000")
	cursor = db.cursor()
	for i in range(121): 
		theId = i+1
		sql = "INSERT INTO " + cities + "(id,name) VALUES (" + str(theId) + ",'city_" + str(theId) + "')"
		try:
			cursor.execute(sql)
			db.commit()
		except:
			db.rollback()
		
	db.close()
	
def insertRestaurants():
	citiesFiles = list(map(lambda l: l.replace('\n',''),open('city_restaurant.txt').readlines()))
	dictOfRestaurantsCities = {x.split('\t')[1]:x.split('\t')[0] for x in citiesFiles}
	
	restaurantCost = list(map(lambda l: l.replace('\n',''),open('restaurant_cost.txt').readlines()))
	dictOfRestaurantsCost = {x.split('\t')[0]:x.split('\t')[1].replace('\n','') for x in restaurantCost}
	
	db = mysql.connector.connect(host="localhost", user="tesis", passwd="tesis", db="tesis_restauratns000")
	cursor = db.cursor()
	
	theId = 0
	for k,v in dictOfRestaurantsCost.items(): 
		theId = theId + 1
		city = '999'
		if k in dictOfRestaurantsCities.keys():
			city = dictOfRestaurantsCities[k]
			
		sql = "INSERT INTO " + restaurants + "(id,name,cost,city) VALUES (" + str(theId) + ",'restaurant_" + str(theId) + "'," + str(v) + ',' + city + ")"
		try:
			cursor.execute(sql)
			db.commit()
		except:
			db.rollback()
		
	db.close()

def insertKitchen():
	db = mysql.connector.connect(host="localhost", user="tesis", passwd="tesis", db="tesis_restauratns000")
	cursor = db.cursor()
	for i in range(290): 
		theId = i+1
		sql = "INSERT INTO " + kitchen + "(id,name) VALUES (" + str(theId) + ",'kitchen_" + str(theId) + "')"
		try:
			cursor.execute(sql)
			db.commit()
		except:
			db.rollback()
		
	db.close()
	
def insertRestaurantKitchen():
	db = mysql.connector.connect(host="localhost", user="tesis", passwd="tesis", db="tesis_restauratns000")
	cursor = db.cursor()
	restaurantKitchen = list(map(lambda l: l.replace('\n',''),open('restaurant_cuisine.txt').readlines()))
	dictOfRestaurantKitchen = {}
	
	for restKit in restaurantKitchen:
		rest = restKit.split('\t')[0]
		kit = restKit.split('\t')[1]
		if rest in dictOfRestaurantKitchen.keys():
			dictOfRestaurantKitchen[rest] = dictOfRestaurantKitchen[rest] + [kit]
		else :
			dictOfRestaurantKitchen[rest] = [kit]
	
	theId = 0
	for k,vl in dictOfRestaurantKitchen.items():
		for v in vl:
			theId = theId + 1
			sql = "INSERT INTO " + restaurantKitchenType + "(id,restaurant,kitchen) VALUES (" + str(theId) + "," + k + "," + v + ")"
			try:
				cursor.execute(sql)
				db.commit()
			except:
				db.rollback()
		
	db.close()

def insertSimilarities():
	db = mysql.connector.connect(host="localhost", user="tesis", passwd="tesis", db="tesis_restauratns000")
	cursor = db.cursor()
	compatIntersection = list(map(lambda l: l.replace('\n',''),open('restaurant_compat_intersection.txt').readlines()))
	compatJaccard = list(map(lambda l: l.replace('\n',''),open('restaurant_compat_jaccard.txt').readlines()))
	
	theId = 0
	for jac in compatJaccard:
		theId = theId + 1
		rest1 = jac.split('\t')[0]
		rest2 = jac.split('\t')[1]
		jacCoef = jac.split('\t')[2]
		sql = "INSERT INTO " + similarity + "(id,restaurant1,restaurant2,inter,jaccard) VALUES (" + str(theId) + "," + rest1 + "," + rest2 + ",0.0," + jacCoef + ")"
		try:
			cursor.execute(sql)
			db.commit()
		except:
			db.rollback()
			
	for inter in compatIntersection:
		rest1 = inter.split('\t')[0]
		rest2 = inter.split('\t')[1]
		interCoef = inter.split('\t')[2]
		sql = "UPDATE " + similarity + " set inter = " + interCoef + " WHERE restaurant1 = " + rest1 + " AND restaurant2 = " + rest2
		try:
			cursor.execute(sql)
			db.commit()
		except:
			db.rollback()
		
	db.close()
	
#insertCities()
#insertRestaurants()
#insertKitchen()
#insertRestaurantKitchen()
insertSimilarities()