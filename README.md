# 🌱 Smart Soil & Pengusir Hama & pH Monitoring System with ESP32-CAM + Telegram Bot

Proyek ini adalah sebuah sistem pemantauan kondisi tanah dan kualitas air yang menggunakan ESP32-CAM yang terhubung ke Telegram Bot. Sistem ini dapat mengirimkan data terkait status tanah (kering, normal, basah), status pompa, nilai pH tanah, serta foto objek (misalnya tanaman atau area tanah) kepada pengguna melalui pesan Telegram. Sistem ini juga memungkinkan pengguna untuk mengontrol beberapa aspek melalui perintah yang dikirimkan ke bot Telegram, seperti menyalakan flash kamera dan meminta foto. [AKAMIGAS]

---

## 🧩 Deskripsi Proyek
Proyek ini merupakan sistem **otomatisasi pemantauan kelembaban tanah dan pH** berbasis **Arduino + ESP32-CAM**, dilengkapi dengan fitur **kamera pemantau dan notifikasi Telegram Bot**.  
Sistem mampu:
- Membaca **kelembaban tanah** dan **nilai pH** menggunakan sensor analog.  
- Mengaktifkan **pompa air dan pompa nutrisi** secara otomatis sesuai kondisi tanah dan pH.  
- Mendeteksi **gerakan (PIR sensor)** sebagai sistem keamanan kebun.  
- Mengirim **notifikasi dan foto** kondisi tanaman secara **real-time ke Telegram**.

---

## ⚙️ Komponen yang Digunakan

| Komponen | Fungsi |
|----------|---------|
| Arduino UNO / Nano | Mengelola pembacaan sensor & kontrol pompa |
| ESP32-CAM (AI Thinker) | Mengambil gambar dan mengirim data ke Telegram |
| Sensor pH Analog | Mengukur tingkat keasaman tanah |
| Sensor Kelembaban Tanah | Mendeteksi kadar air pada tanah |
| Sensor PIR | Mendeteksi gerakan di sekitar area tanam |
| Relay Module (2 Channel) | Mengendalikan pompa air dan nutrisi |
| Buzzer & LED | Memberi peringatan visual dan suara |
| LCD 16x2 I2C | Menampilkan status sensor |
| Modul WiFi ESP32-CAM | Koneksi internet & komunikasi dengan Telegram |
| Kabel jumper, breadboard, power supply | Pendukung koneksi sistem |

---

## 🔗 Diagram Koneksi Singkat

### **Arduino**
| Pin Arduino | Komponen |
|--------------|-----------|
| A1 | Sensor Kelembaban Tanah |
| A2 | Sensor pH |
| A3 | Sensor Kalibrasi pH |
| D3 | LED Indikator |
| D5 | Sensor PIR |
| D6 | Buzzer |
| D7 | Relay Nutrisi |
| D8 | Relay Pompa |
| D9 | RX ke ESP32-CAM (TX2) |
| D10 | TX ke ESP32-CAM (RX2) |

### **ESP32-CAM (AI Thinker)**
| Pin ESP32-CAM | Keterangan |
|----------------|-------------|
| GPIO14 (RX2) | Terhubung ke TX Arduino |
| GPIO15 (TX2) | Terhubung ke RX Arduino |
| GPIO4 | LED Flash Kamera |
| Power 5V & GND | Sumber daya sistem |

---

## 💡 Fitur Utama

### 1. **Monitoring Otomatis**
- Membaca kelembaban tanah (`Soil Moisture`) dan nilai pH.  
- Menentukan status tanah:
  - 🌊 **Basah** → Pompa OFF  
  - 🌤 **Normal** → Pompa OFF  
  - 🔥 **Kering** → Pompa ON  
- Mengontrol **nutrisi otomatis** berdasarkan nilai pH:
  - pH < batas → **Asam**, nutrisi diaktifkan  
  - pH normal → **Stabil**  
  - pH > batas → **Basa**, nutrisi diaktifkan  

### 2. **Komunikasi Serial Antar Mikrokontroler**
Arduino mengirimkan data sensor ke ESP32-CAM melalui **SoftwareSerial**:
 - #1! → Status Tanah
 - #11! → Status pH Asam
 - #22! → Status pH Normal
 - #33! → Status pH Basa
 - #PH@ → Nilai pH aktual

### 3. **Integrasi Telegram Bot**
ESP32-CAM menerima perintah dari pengguna dan mengirimkan:
- 📷 **Foto real-time** dari area tanaman.
- 📊 **Status tanah & pH.**
- 💡 Perintah via Telegram:
  - /start → Petunjuk penggunaa
  - /photo → Mengambil foto terbaru
  - /flash → Menghidupkan/mematikan LED flash kamera
  - /cekkondisi → Menampilkan kondisi tanah + foto objek
 
### 4. **Sistem Keamanan PIR**
Sensor PIR akan mendeteksi gerakan dan menyalakan **buzzer serta LED** sebagai alarm singkat.

---

## 🧠 Alur Kerja Sistem

1. Arduino membaca nilai dari:
 - Sensor kelembaban tanah  
 - Sensor pH tanah  
 - Sensor PIR  
2. Arduino menampilkan data di LCD dan mengirim data sensor via serial ke ESP32-CAM.
3. ESP32-CAM:
 - Menerima data serial dan mengidentifikasi status tanah & pH.
 - Mengirim laporan kondisi ke **Telegram**.
 - Mengambil **foto otomatis** bila diminta oleh pengguna atau kondisi kritis (tanah kering / pH tidak normal).

---

## 📱 Tampilan Telegram Bot

| Command | Fungsi | Contoh Respon |
|----------|---------|----------------|
| `/start` | Menampilkan panduan bot | *Selamat Datang, gunakan /photo atau /cekkondisi* |
| `/photo` | Mengirim foto terbaru | *(Gambar tanaman terkirim)* |
| `/flash` | Menyalakan/menonaktifkan flash | *Flash ON / OFF* |
| `/cekkondisi` | Menampilkan data sensor & foto | *Status Tanah: Normal, PH: 6.8, Pompa OFF* |

---

## Contacs us : 
* [Frendi RoboTech](https://www.instagram.com/frendi.co/)
* [Whatsapp : +6287888227410](https://wa.me/+6287888227410)
* [Email    : frendirobotech@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendirobotech@gmail.com) atau [Email    : frendix45@gmail.com](https://mail.google.com/mail/u/0/?view=cm&tf=1&fs=1&to=frendix45@gmail.com)

---

## 👨‍💻 Author
Dikembangkan oleh: Imam Sa'id Nurfrendi [Reog Robotic & Robotech Electronics]  
Lisensi: Open Source (MIT)
