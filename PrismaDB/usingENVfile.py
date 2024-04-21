# importing os module for environment variables
import os
# importing necessary functions from dotenv library
from dotenv import load_dotenv, dotenv_values
import asyncio
from bson import ObjectId
const id = new ObjectId()

# loading variables from .env file
load_dotenv('ari_file.env')

# accessing and printing value
dbURL = os.getenv("DATABASE_URL")

print(dbURL)

datasource db{
  provider = "mongodb"
  url      = dbURL
}