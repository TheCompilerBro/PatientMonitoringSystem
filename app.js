// ---------------- Firebase Modules ----------------
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.6.1/firebase-app.js";
import {
    getDatabase,
    ref,
    onValue,
    update
} from "https://www.gstatic.com/firebasejs/9.6.1/firebase-database.js";

// ---------------- Firebase Config ----------------
const firebaseConfig = {
  apiKey: "AIzaSyDsfLzKSuId6bZQzraGX9icbc03Age1PvQ",
  authDomain: "patient-monitoring-syste-dd78b.firebaseapp.com",
  databaseURL: "https://patient-monitoring-syste-dd78b-default-rtdb.firebaseio.com/",
  projectId: "patient-monitoring-syste-dd78b",
  storageBucket: "patient-monitoring-syste-dd78b.firebasestorage.app",
  messagingSenderId: "240750870782",
  appId: "1:240750870782:web:20315e9a1a92caebcf65af"
};

const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

// ---------------- Elements ----------------
const flexBox = document.getElementById("flexValue");
const fallBox = document.getElementById("fallValue");
const tempBox = document.getElementById("tempValue");
const timeBox = document.getElementById("timeValue");
const alertBanner = document.getElementById("alertBanner");
const historyList = document.getElementById("historyList");

// ---------------- Alert Sound ----------------
let alertSound = new Audio("beep.mp3");

// *** IMPORTANT FIX: Unlock audio ***
document.getElementById("enableSoundBtn").onclick = () => {
    alertSound.play().then(() => {
        alertSound.pause();
        alertSound.currentTime = 0;
        console.log("Audio unlocked!");
        document.getElementById("enableSoundBtn").style.display = "none";
    });
};

// ---------------- Show Alert Function ----------------
function showAlert(msg) {
    alertBanner.innerHTML = msg;
    alertBanner.classList.remove("hidden");

    // Play alert sound
    alertSound.currentTime = 0;
    alertSound.play();

    if (navigator.vibrate) navigator.vibrate(400);

    let li = document.createElement("li");
    li.textContent = `${msg} | ${new Date().toLocaleString()}`;
    historyList.prepend(li);

    update(ref(db, "alerts"), { message: "none" });

    setTimeout(() => alertBanner.classList.add("hidden"), 5000);
}

// ---------------- Firebase Listener ----------------
onValue(ref(db, "alerts"), (snapshot) => {
    const data = snapshot.val();
    if (!data) return;

    flexBox.innerHTML = data.flex;
    fallBox.innerHTML = data.fall;
    tempBox.innerHTML = data.temperature;
    timeBox.innerHTML = data.time;

    if (data.message !== "none" && data.message && data.message !== "") {
        showAlert(data.message);
    }
});
