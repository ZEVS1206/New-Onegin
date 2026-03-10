# Onegin

![C](https://img.shields.io/badge/language-C-blue.svg)
![G++](https://img.shields.io/badge/compiler-g++-orange.svg)
![Makefile](https://img.shields.io/badge/build-Makefile-green.svg)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)
![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)

## 📖 About the Project

**Onegin** is an educational project that implements efficient **alphabetical sorting of large text datasets**.

The program reads a large text file, processes it line by line, and sorts the lines alphabetically using custom comparison rules.
This project is typically used to practice:

* working with **large text buffers**
* **file I/O**
* **custom string comparators**
* **sorting algorithms**

The project name is inspired by the classic Russian novel *"Eugene Onegin"* by Alexander Pushkin, which is often used as a dataset for similar programming exercises.

---

## ✨ Features

* 📂 Reads and processes **large text files**
* 🔤 Sorts lines **alphabetically**
* 🔁 Supports **custom comparison logic**
* ⚡ Efficient handling of large buffers
* 🧹 Ignores punctuation when comparing strings 

---

## 🛠 Technologies Used

* **C**
* **g++**
* **Makefile**
* **Standard Library**
* **File I/O**

---

## 📂 Project Structure

```
Onegin/
│
├── source/         # Source files
├── include/        # Header files
├── build/          # Compiled binaries
├── Makefile        # Build configuration
└── README.md
```

---

## ⚙️ Build and Run


### Clone the repository

```bash
git clone https://github.com/yourusername/New-Onegin.git
cd New-Onegin
```

### Prepare your text
You need to add text for analysis to file **Input.txt**

### Build the project

```bash
make
```

### Run

```bash
make run
```

---

## 🧠 How It Works

1. The program reads the entire text file into memory.
2. The text is split into separate lines.
3. An array of pointers to these lines is created.
4. The array is sorted using a custom comparator.
5. The sorted result is written to filt **Output.txt**.

This approach avoids unnecessary copying and allows efficient sorting of large text datasets.

---

## 📚 Educational Purpose

This project was created as part of a programming course to practice:

* pointer manipulation
* memory management
* sorting algorithms
* working with large files

---

## 📄 License

This project is licensed under the **MIT License**.

---

## 👨‍💻 Author

This project is a part of [Ilya Dedinskiy's](https://vk.com/ded32_ru) course of C-language!

Created by [Zevs](https://github.com/ZEVS1206)
