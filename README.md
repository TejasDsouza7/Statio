# 🛰️ Statio

**Statio** is a real-time satellite tracking CLI app written in **C++**. It uses the **N2YO API** to track the ISS and satellites above your location, and pulls metadata like country, purpose, and launch date from **Space-Track.org**.

---

## ✨ Features

- 🔭 Track the **ISS** and any satellite via **NORAD ID**
- 📍 Show all satellites **currently above** your location
- 🌐 Auto-detects your **geolocation**
- 🏳 Fetch satellite metadata: country, purpose, launch date

---

## 🛠️ Setup Instructions

### 1. Clone the repo

```bash
git clone https://github.com/TejasDsouza7/Statio.git
cd Statio
```
### 2. Install dependencies

```bash

sudo pacman -S curl
JSON parsing is handled with nlohmann/json (included in include/)
```
### 🔐 Required Environment Variables

- Before running `Statio`, you need to add your API keys and login credentials in the `.env` file.

```bash
N2YO_API_KEY=your_n2yo_api_key_here
SPACETRACK_USER=your_spacetrack_username
SPACETRACK_PASS=your_spacetrack_password
```

- 🔑 Get your N2YO API key From www.n2yo.com

- 🛰️ Register on Space-Track.org 

### Make sure to export them before running:

```bash
export $(grep -v '^#' .env | xargs)
```
### ⚙️ Building & Running

- Compile:

```bash
make
```
- Run:

```bash
./statio
```


