import sqlite3 as mysql
connection = mysql.connect('foodmenu.db')
cursor = connection.cursor()
cursor.execute("""
CREATE TABLE IF NOT EXISTS menu (
    id INT,
    meal TEXT,
    price INT,
    lettuce BIT,
    tomato BIT,
    onion BIT,
    pickles BIT,
    mayonnaise BIT,
    alootikki BIT,
    paneertikki BIT,
    chickentikki BIT,
    chickennuggets BIT,
    veggies BIT,
    chipotlesauce BIT,
    corn BIT,
    paneernuggets BIT,
    fries BIT,
    spicysauce BIT,
    brocolli BIT
    
)
""")

cursor.execute("""
INSERT INTO menu VALUES
(101, 'Aloo Tikki Burger',69,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0),
(102, 'Chicken Tikki Burger',109,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,0),
(103, 'Fresh Burger',99,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0),
(104, 'Crispy Paneer Burger',89,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0),
(105, 'Paneer Wrap',109,1,1,1,1,1,0,0,0,0,1,1,0,1,0,0,1),
(106, 'Chicken Wrap',139,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1),
(107, 'Paneer Sandwich',119,1,1,1,1,1,0,0,0,0,1,1,0,1,0,0,1),
(108, 'Chicken Wrap',169,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1)
""")

cursor.execute("""
CREATE TABLE IF NOT EXISTS drinksmenu (
    id INT,
    drinkname TEXT,
    price INT,
    water BIT,
    soda BIT,
    ice BIT,
    lemon BIT,
    sugar BIT,
    salt BIT,
    watermelonjuice BIT,
    strawberryjuice BIT,
    milk BIT

)
""")

cursor.execute(
    """
    INSERT INTO drinksmenu VALUES
    (201,"Iced Lemonade",59,1,0,1,1,1,1,0,0,0),
    (202,"Lemon Soda",69,0,1,1,1,1,1,0,0,0),
    (203,"Watermelon Mojito",89,0,1,1,1,1,1,1,0,0),
    (204,"Strawberry Mojito",89,0,1,1,1,1,1,0,1,0),
    (205,"Strawberry Milkshake",149,0,0,1,0,1,1,0,1,1)
    """
)
connection.commit()
connection.close()