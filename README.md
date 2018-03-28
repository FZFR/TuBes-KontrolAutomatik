#### Bagi yang nitip buatin kodingan ada di folder:
[/src/main/examples] (https://github.com/Fazzafr/TuBes-KontrolAutomatik/blob/master/src/main/examples/)

# TuBes-KontrolAutomatik
Tugas Besar mata kuliah Kontrol Automatik menggunakan sensor ultrasonic, pompa air mini, flowmeter dan servo. 
Mengukur Q3(debit keluar) terhadap H1(ketinggian Tank 1)
<ul><li>Sensor Ultrasonic membaca ketinggian air di Tank 1 </li>
<li>Jika sudah sesuai setpoint(perbandingan debit keluar dan ketinggian), maka servo akan menutup keran.</li>
<li>Jika kurang, servo akan membuka keran, sehingga air akan mengalir dari reservoir</li>


## Keterangan dan prosedur kerja:
+ Karakterisasi nilai H1 terhadap Q3, buat sistem dalam keadaan maksimum(semua keran dibuka full) dan Q1 serta Q2 hidup(Pompa air).
+ Setelah keadaan ketinggian sudah konstan maka lepas pompa air Q1 dan Q2.
+ Hitung nilai H1 dan Q3.
+ Plot nilai H1 dan Q3 pada software(saya menggunakan excel) dimana x=H1 dan y=Q3
+ Cari persamaan linearitasnya
+ setelah dapat persamaannya, input yang kita masukkan berupa set point Q yang kita inginkan, misal setpoint = 100L/jam serta PID menggunakan konsep Ziegler Nichols Kp=..., Ki=..., Kd...
+ Pada kodingan, setpoint diubah kee H1 menggunakan persamaan yang ada lalu PID akan bekerja setelah nilai setpoint di konversi ke H1, lihat sensor flow Q3 yang di dapat.
+ Lihat nilai setpoint dengan nilai real yang dibaca sensor Q3 untuk dapat error.
+ Tujuan memakai PID adalah untuk menjaga aliran tetap pada setpoint yang kita inginkan, jadi jika aliran yang kita inginkan 100L/Jam maka valve akan membuka dan menutup untuk mempertahankan setpoint yang diinginkan.




