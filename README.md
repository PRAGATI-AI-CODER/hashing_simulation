# HashHero – Animated Hashing Simulator (C + BGI Graphics)

HashHero is an interactive **hashing visualization tool** built using the classic **BGI graphics library**.  
It visually demonstrates how hashing, modulo operation, collisions, and linear probing work internally.

This project is perfect for students learning **Data Structures**, especially **Hash Tables**.

---

## 🚀 Features

- 🧮 Hash function: `index = key % slots`
- 🔁 Collision handling using **Linear Probing**
- 🕹 Animated “Hero” character carrying the key
- ⚡ Collision cells flash red
- 🔊 Success and collision beep effects
- 📊 Right-side message panel
- 🎨 Dynamic hash table boxes with key display

---

## 📁 Project Contents



├── hashhero.c # Main program source
└── README.md # Documentation


---

# 🖥 How to Run in Turbo C (DOSBox)

### 1️⃣ Install Turbo C++ with DOSBox (common student package)

### 2️⃣ Place your `hashhero.c` file here:


C:\TURBOC3\BIN\


### 3️⃣ Ensure the BGI folder exists:


C:\TURBOC3\BGI\


### 4️⃣ The code already contains the correct line:
```c
initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

5️⃣ Open Turbo C → File → Open → hashhero.c
6️⃣ Compile:
Alt + C → C

7️⃣ Run:
Ctrl + F9


✔ A graphics window will open
✔ The hero will move, insert keys, handle collisions, and animate everything

🖥 How to Run in Dev-C++ / Code::Blocks (WinBGIm)
1️⃣ Install WinBGIm graphics library
2️⃣ Create new C project
3️⃣ Add hashhero.c
4️⃣ Add these linker flags (only for WinBGIm):
-lbgi -lgdi32 -lcomdlg32 -luuid -lole32 -lws2_32

5️⃣ Build & Run

A graphics window will appear and show the full animation.



📚 Learning Outcomes

Using HashHero, students learn:

How hashing works

How modulo (%) calculates slot index

Why collisions happen

How linear probing resolves collisions

How elements get stored in a hash table

How arrays + probing create continuous search

It turns a complex data structure into a fun visual demonstration.

🤝 Contributing

Want to improve HashHero? You can add:

Quadratic probing

Double hashing

More animations

Better hero sprite

Sound effects

Table resizing

Pull requests are welcome!

📜 License

This project is open for educational and personal use.

👩‍💻 Developer

PRAGATI-AI-CODER
Creator of HashHero – Visual Hashing Simulation
