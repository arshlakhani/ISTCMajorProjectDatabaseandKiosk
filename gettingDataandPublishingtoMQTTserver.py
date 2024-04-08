import json
import sqlite3 as mysql
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print('CONNACK received with code %d.' % (rc))

clientID = "arsh"
broker = "mqtt-dashboard.com"
port = 8884

def publishdata(clientID,  broker, port, topic, foodID):
    pub = mqtt.Client(clientID)
    pub.on_connect = on_connect
    pub.connect('broker.mqttdashboard.com', 1883)
    connection = mysql.connect('foodmenu.db')
    cursor = connection.cursor()
   
    if foodID < 200:
        cursor.execute('SELECT * FROM menu WHERE id = {}'.format(foodID))
        row_headers = [x[0] for x in cursor.description]
        rows = cursor.fetchall()
        print(rows)
        json_data = []
        for row in rows:
            json_data.append(dict(zip(row_headers, row)))
        json_Data = json.dumps(json_data)
        print(json_Data)
    else:
        cursor.execute('SELECT * FROM drinksnew WHERE id = {}'.format(foodID))
        row_headers = [x[0] for x in cursor.description]
        rows = cursor.fetchall()
        print(rows)
        json_data = []
        for row in rows:
            json_data.append(dict(zip(row_headers, row)))
        json_Data = json.dumps(json_data)
        print(json_Data)
    pub.publish(topic,f"{json_Data}",qos= 1)
    connection.commit()
    connection.close()