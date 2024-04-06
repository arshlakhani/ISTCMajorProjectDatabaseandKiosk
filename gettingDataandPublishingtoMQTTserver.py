import json
import sqlite3 as mysql
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print('CONNACK received with code %d.' % (rc))

clientID = "arsh"
broker = "mqtt-dashboard.com"
port = 8884
pub = mqtt.Client(clientID)

pub.on_connect = on_connect
pub.connect('broker.mqttdashboard.com', 1883)
pub.publish("testtopicnew/1","hi",qos= 1)
connection = mysql.connect('foodmenu.db')
cursor = connection.cursor()
orderID = int(input("What food are we making today"))
ordertype = input('d for drink and f for food')
if ordertype == 'f':
    cursor.execute('SELECT * FROM menu WHERE id = {}'.format(orderID))
    row_headers = [x[0] for x in cursor.description]
    rows = cursor.fetchall()
    print(rows)
    json_data = []
    for row in rows:
        json_data.append(dict(zip(row_headers, row)))
    json_Data = json.dumps(json_data)
    print(json_Data)
if ordertype == 'd':
    cursor.execute('SELECT * FROM drinksmenu WHERE id = {}'.format(orderID))
    row_headers = [x[0] for x in cursor.description]
    rows = cursor.fetchall()
    print(rows)
    json_data = []
    for row in rows:
        json_data.append(dict(zip(row_headers, row)))
    json_Data = json.dumps(json_data)
    print(json_Data)
pub.publish("testtopicnew/1",f"{json_Data}",qos= 1)
connection.commit()
connection.close()