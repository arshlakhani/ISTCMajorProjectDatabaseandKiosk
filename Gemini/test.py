import google.generativeai as genai
import time
genai.configure(api_key="AIzaSyBiyRdSJFuRU2C9bKgUV5qSojfmaOmY-nE")



def RecommendNewFood(lastEatenfood):
    model = genai.GenerativeModel('gemini-1.5-pro-latest')
    response = model.generate_content("We have 'Aloo Tikki Burger','Chicken Tikki Burger','Fresh Burger','Crispy Paneer Burger','Chicken Wrap', 'Paneer Sandwich','Chicken Wrap' in the menu and customer just ate{} what should he try next, Give 3 recommendation".format(lastEatenfood))
    print(response.text)

RecommendNewFood("Chicken Tikki Burger")