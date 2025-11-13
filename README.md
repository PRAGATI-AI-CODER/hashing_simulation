✅ README.md (Final Version — Just Copy & Paste)
# HashHero – Animated Hashing Simulator (C + BGI Graphics)

HashHero is a fun and interactive **visual hashing simulation** built using the old-school **BGI graphics library** (Turbo C / WinBGIm).  
It shows how hashing works internally using:

- Key hashing (`key % slots`)
- Linear probing
- Collision detection
- Step-by-step animation
- A moving “hero” character carrying keys
- Flashing collision cells
- Success & collision sounds

This project helps students understand **open addressing hashing** in a visual and enjoyable way.

---

## 🚀 Features

✔ Animated insertion of keys  
✔ Custom hero character that carries numbers  
✔ Collision flashing (red highlight)  
✔ Linear probing movement  
✔ Success + collision beep sounds  
✔ Real-time step / message panel  
✔ Slot indexing displayed  
✔ Easy to run in Turbo C or WinBGIm  

---

## 🧪 Hashing Technique Used

- **Hash Function:**  


index = key % slots

- **Collision Handling:**  
✔ Linear Probing (`(index + 1) % slots`)

---

## 📁 Project Structure



├── hashhero.c # Main source code
└── README.md # Documentation


---

# 🖥 How to Run (Turbo C / DOSBox)

### 1️⃣ Place files in your Turbo C directory:


C:\TURBOC3\BIN\


### 2️⃣ Make sure BGI folder path exists:


C:\TURBOC3\BGI\


### 3️⃣ Edit this line in the code (Already set):
```c
initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

4️⃣ Open Turbo C → File → Open → hashhero.c
5️⃣ Compile: Alt + C → C
6️⃣ Run: Ctrl + F9
A graphics window will appear showing:

Hash table

Hero animation

Key insertion

Collision flashing

Beep sounds

🖥 How to Run (Dev-C++ / Code::Blocks + WinBGIm)

To use the modern version of this program:

1️⃣ Install WinBGIm graphics library
2️⃣ Create a new C project
3️⃣ Add hashhero.c
4️⃣ Add these linker flags:
-lbgi -lgdi32 -lcomdlg32 -luuid -lole32 -lws2_32

5️⃣ Build & Run

A BGI graphics window will open.

📸 Screenshots (You can add later)

Add screenshots of the animation here once you run it.

Example:

![Hash Table Animation](screenshots/demo.png)

📚 Learning Outcome

This project helps students understand:

Hash functions

Modulo indexing

Collision resolution

Linear probing

Table traversal

Visual debugging of hashing

Perfect for:

DSA assignments

College lab submissions

Visualization projects

Teaching classmates

🤝 Contributing

Feel free to fork and add:

Quadratic probing

Double hashing

New hero sprites

Better animations

Sound improvements

📜 License

This project is open-source.
You may modify and use it for personal or educational purposes.

👩‍💻 Developer

PRAGATI-AI-CODER
HashHero – Visual Hash Table Simulation Project
