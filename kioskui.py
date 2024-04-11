from customtkinter import *
app = CTk()
app.geometry("800x450")

set_appearance_mode("dark")
label = CTkLabel(master=app,fg_color="transparent",text_color="#ffffff",text="Kiosk")
label.place(relx=0.5,rely=0.3,anchor="center")


def ordermenu():
    new_window = CTkToplevel()
    new_window.geometry("800x450")
    set_appearance_mode("dark")
    new_window.title("Ordering...")
    burgerLabel = CTkLabel(master=new_window,text="Burgers!",fg_color="transparent",text_color="white",height=36,font=('Helvetica', 16, 'bold'))
    burgerLabel.place(relx=0.05,rely=0.1,anchor="center")
    
btn = CTkButton(master = app, text="Start Ordering!", corner_radius=32,fg_color="#9e0af2", hover_color="#a834eb",border_color="#d6c8de",command=ordermenu )
btn.place(relx = 0.5, rely=0.5, anchor="center")

app.mainloop()