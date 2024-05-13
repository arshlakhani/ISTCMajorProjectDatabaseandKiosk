import os
import pymongo
from dotenv import load_dotenv, dotenv_values

# loading variables from .env file
load_dotenv('ari_file.env')

# accessing and printing value
dbURL = os.getenv("DATABASE_URL")

print(dbURL)

client = pymongo.MongoClient(dbURL)
print(client)