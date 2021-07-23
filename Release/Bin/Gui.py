from tkinter import *
from tkinter import ttk
from tkinter import filedialog
import time
import os
import sys
import subprocess

root = Tk()

root.title("Search Engine")
root.iconbitmap('Image//icon.ico')

root.geometry("600x600")
# background image
bg_image = PhotoImage(file='Image//background.png')
bg_label = Label(root, image=bg_image)
bg_label.place(relwidth=1, relheight=1)
# progress bar


def start():
    for i in range(0, 100, 50):
        time.sleep(1)
        bar['value'] += 50
        if(i == 50):
            os.system("GUIQuery.exe" + " " + entry.get() +
                      " " + str(variable.get()))
            global button_pre
            global button_next
            global status
            global mytext
            global myname
            global myscore
            global li
            mytext.delete(1.0, END)
            myname.delete(1.0, END)
            myscore.delete(1.0, END)
            button_pre.place_forget()
            button_next.place_forget()
            status.place_forget()
            li = []
            for folder in os.listdir("..\\File"):
                li = li + open_file(os.path.join("..\\File", folder))
                if len(li) >= variable.get():
                    break
            li = li[:variable.get()]
            if len(li) == 0:
                return
            status = Label(lower_frame, text="1 of " + str(len(li)))
            status.place(rely=0.95, relx=0.1, relheight=0.05, relwidth=0.8)
            button_pre = Button(lower_frame, text="<<", command=lambda: pre(0))
            button_next = Button(lower_frame, text=">>",
                                 command=lambda: next(0))
            button_pre.place(rely=0.95, relheight=0.05, relwidth=0.1)
            button_next.place(rely=0.95, relx=0.9,
                              relheight=0.05, relwidth=0.1)
            next(-1)

        root.update_idletasks()
    bar['value'] = 0


bar = ttk.Progressbar(root, orient=HORIZONTAL, length=300)
bar.place(relx=0.1, rely=0.9, relwidth=0.8, relheight=0.05)

# frame introduction
frame_intro = Frame(root, bg='white', bd=5)
frame_intro.place(relheight=0.1, relwidth=1)
# logo
lg_image = PhotoImage(file='image//try_2.png')
lg_label = Label(frame_intro, image=lg_image)
lg_label.place(relx=-0.1, rely=0.1, relwidth=0.75, relheight=0.8)
# add button


def open_and_import():
    foldername = filedialog.askdirectory(
        initialdir="..\File", title="Select folder to import")
    print(foldername)
    for i in range(0, 100, 20):
        time.sleep(1)
        bar['value'] += 20
        if i == 60:
            os.system("GUIModifyIndex.exe Update " + foldername + " 1")
        root.update_idletasks()
    bar['value'] = 0


def clear():
    for i in range(0, 100, 50):
        time.sleep(1)
        bar['value'] += 50
        if i == 50:
            os.system("GUIModifyIndex.exe Clear")
        root.update_idletasks()
    bar['value'] = 0


add_button = Button(frame_intro, text="Add",
                    font="Raleway", fg="white", bg='#20bebe', command=open_and_import)
add_button.place(relx=0.75, rely=0.1, relheight=0.8, relwidth=0.1)
# remove button
remove_button = Button(frame_intro, text="Clear",
                       font="Raleway", fg="white", bg='#20bebe', command=clear)
remove_button.place(relx=0.86, rely=0.1, relheight=0.8, relwidth=0.14)


# frame for search
frame_searchbar = Frame(root, bg='#20bebe', bd=5)
frame_searchbar.place(relx=0.05, rely=0.12, relwidth=0.9, relheight=0.07)
# search
entry = Entry(frame_searchbar, font=40)
entry.place(relwidth=0.65, relheight=1)
# Number
OPTIONS = [1, 5, 10, 15, 20, 25, 30]
variable = IntVar(frame_searchbar)
variable.set(OPTIONS[1])

entry_Ndoc = OptionMenu(frame_searchbar, variable, *OPTIONS)
entry_Ndoc.config(bg='white')
entry_Ndoc["menu"].config(bg='white')
entry_Ndoc.place(relx=0.66, relwidth=0.1, relheight=1)
# button_search
button = Button(frame_searchbar, text="Search",
                font="Raleway", fg="white", bg='#20bebe', bd=5, command=start)
button.place(relx=0.76, relheight=1, relwidth=0.23)


def open_file(search_folder):  # return list contents
    f = open("logdoc.txt", "r")
    cnt = int(f.readline())
    _li = []
    for _ in range(cnt):
        name = f.readline()[:-1]
        score = f.readline()
        path = os.path.join("..\\File", search_folder)
        for folder in os.listdir(path):
            sub_path = os.path.join(path, folder)
            path_name = os.path.join(sub_path, name)
            if(os.path.isfile(path_name)):
                content = open(
                    path_name, "r", encoding='utf-16-le').read(1000) + '...'
                _li.append([content, score, name])
    return _li


def next(id):
    global mytext
    global myname
    global myscore
    global button_pre
    global button_next
    global li
    global status
    mytext.delete(1.0, END)
    myname.delete(1.0, END)
    myscore.delete(1.0, END)

    button_pre.place_forget()
    button_next.place_forget()
    status.place_forget()

    nxt_id = (id + 1) % (len(li))
    mytext.insert(1.0, li[nxt_id][0])

    myname = Text(lower_frame)
    Font_tuple = ("Times New Roman", 10, "bold")
    myname.configure(font=Font_tuple)
    mytext.configure(font=Font_tuple)

    myname.tag_configure("center", justify="center")
    myname.tag_add("center", 1.0, "end")
    myscore.tag_configure("center", justify="center")
    myscore.tag_add("center", 1.0, "end")

    myname.insert(1.0, li[nxt_id][2])
    myname.place(relwidth=0.1, relheight=0.95)

    myscore = Text(lower_frame)
    myscore.configure(font=("Calibri Light", 13, "bold"))
    myscore.insert(1.0, li[nxt_id][1])
    myscore.place(relx=0.1, relwidth=0.1, relheight=0.95)

    status = Label(lower_frame, text=str(nxt_id + 1) +
                   " of " + str(len(li)), bg='white')
    status.place(rely=0.95, relx=0.1, relheight=0.05, relwidth=0.8)
    button_pre = Button(lower_frame, text="<<", command=lambda: pre(
        nxt_id), fg='white', bg='#20bebe')
    button_next = Button(lower_frame, text=">>", command=lambda: next(
        nxt_id), fg='white', bg='#20bebe')

    button_pre.place(rely=0.95, relheight=0.05, relwidth=0.1)
    button_next.place(rely=0.95, relx=0.9, relheight=0.05, relwidth=0.1)


def pre(id):
    global mytext
    global myname
    global myscore
    global button_pre
    global button_next
    global li
    global status
    mytext.delete(1.0, END)
    myname.delete(1.0, END)
    myscore.delete(1.0, END)

    button_pre.place_forget()
    button_next.place_forget()
    status.place_forget()

    pre_id = (id - 1 + len(li)) % (len(li))
    mytext.insert(1.0, li[pre_id][0])

    myname = Text(lower_frame)
    Font_tuple = ("Times New Roman", 10, "bold")
    myname.configure(font=Font_tuple)
    mytext.configure(font=Font_tuple)

    myname.tag_configure("center", justify="center")
    myname.tag_add("center", 1.0, "end")
    myscore.tag_configure("center", justify="center")
    myscore.tag_add("center", 1.0, "end")

    myname.insert(1.0, li[pre_id][2])
    myname.place(relwidth=0.1, relheight=0.95)

    myscore = Text(lower_frame)
    myscore.insert(1.0, li[pre_id][1])
    myscore.place(relx=0.1, relwidth=0.1, relheight=0.95)
    myscore.configure(font=("Cambria Math", 10, "bold"))

    status = Label(lower_frame, text=str(pre_id + 1) +
                   " of " + str(len(li)), bg='white')
    status.place(rely=0.95, relx=0.1, relheight=0.05, relwidth=0.8)
    button_pre = Button(lower_frame, text="<<", command=lambda: pre(
        pre_id), fg='white', bg='#20bebe')
    button_next = Button(lower_frame, text=">>", command=lambda: next(
        pre_id), fg='white', bg='#20bebe')

    button_pre.place(rely=0.95, relheight=0.05, relwidth=0.1)
    button_next.place(rely=0.95, relx=0.9, relheight=0.05, relwidth=0.1)


# # frame for text
lower_frame = Frame(root, bg='#20bebe', bd=10, borderwidth=5)
lower_frame.place(relx=0.05, rely=0.35, relwidth=0.9, relheight=0.5)
# list content


# li = open_file("VanBanTV_train")
li = []
for folder in os.listdir("..\\File"):
    li = li + open_file(os.path.join("..\\File", folder))
    if len(li) > variable.get():
        break

mytext = Text(lower_frame)

# if len(li):
#     mytext.insert(1.0, li[0][0])
mytext.place(relx=0.2, relwidth=0.8, relheight=0.95)
myname = Text(lower_frame)
# if len(li):
#     myname.insert(1.0, "NAME")
myname.place(relwidth=0.1, relheight=0.95)
myscore = Text(lower_frame)
# if len(li):
#     myscore.insert(1.0, li[0][1])
myscore.place(relx=0.1, relwidth=0.1, relheight=0.95)
# button
status = Label(lower_frame, text="0 of 0", bg='white')
status.place(rely=0.95, relx=0.1, relheight=0.05, relwidth=0.8)
button_pre = Button(lower_frame, text="<<", fg='white', bg='#20bebe')
button_next = Button(lower_frame, text=">>", fg='white', bg='#20bebe')
button_pre.place(rely=0.95, relheight=0.05, relwidth=0.1)
button_next.place(rely=0.95, relx=0.9, relheight=0.05, relwidth=0.1)

# # information
info_frame = Frame(root, bg='#20bebe', bd=5)
info_frame.place(relx=0.05, rely=0.29, relwidth=0.9, relheight=0.06)
info_name = Label(info_frame, text="NAME", bg='white',
                  font=('Segoe UI', 10, 'bold'))
info_name.place(relheight=1, relwidth=0.1)
info_text = Label(info_frame, text="TEXT", bg='white',
                  font=('Segoe UI', 10, 'bold'))
info_text.place(relx=0.2, rely=0, relheight=1, relwidth=0.8)
info_score = Label(info_frame, text="SCORE", bg='white',
                   font=('Segoe UI', 10, 'bold'))
info_score.place(relx=0.1, relheight=1, relwidth=0.1)


root.mainloop()
