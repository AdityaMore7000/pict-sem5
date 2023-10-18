import pymongo

myclient = pymongo.MongoClient("mongodb://localhost:27017/")

mydb = myclient["te31152_db"]

mycol = mydb["laptops"]
for x in mycol.find():
    print(x)

mycol.insert_one({"name":"Dell Isnpiro 5500","price":69,"year":2022})

mycol = mydb["laptops"]
for x in mycol.find():
    print(x)

mycol.update_one({"price":69},{"$set":{"price":70}})

mycol = mydb["laptops"]
for x in mycol.find():
    print(x)

mycol.delete_one({"price":70})
mycol = mydb["laptops"]
for x in mycol.find():
    print(x)
