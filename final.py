from flask import Flask, render_template, request
import subprocess

app = Flask(__name__)

open("patients.txt", "w").close()


@app.route("/", methods=["GET", "POST"])
def home():

    if request.method == "POST":
        p_name = request.form["name1"]
        age = request.form["age1"]
        symptoms = request.form["symptoms1"]
        start_time = request.form["start_time1"]
        end_time = request.form["end_time1"]

        with open("patients.txt", "a") as f:
            f.write(p_name + " " + age + "\n")
            f.write(symptoms + "\n")
            f.write(start_time + " " + end_time + "\n")
        with open("patients.txt", "r") as f:
            lines = f.readlines()

        patient_count = len(lines) // 3
        if patient_count == 5:
            subprocess.run(["./final.exe"])
            appointment_times = [
                "12:00",
                "12:30",
                "13:00",
                "13:30",
                "14:00",
                "14:30",
                "15:00",
                "15:30",
                "16:00",
                "16:30",
                "17:00",
                "17:30",
                "18:00"
            ]
            result = []

            with open("result.txt", "r") as f:

                for line in f:

                    data = line.strip().split(",")

                    result.append({
                        "name": data[0],
                        "score": data[1]
                    })
            patients_data = []

            with open("patients.txt", "r") as f:

                lines = f.readlines()

                for i in range(0, len(lines), 3):

                    name_age = lines[i].strip()
                    times = lines[i + 2].strip().split()

                    patients_data.append({
                        "name": name_age.split()[0],
                        "start": times[0],
                        "end": times[1]
                    })
            used = []

            for patient in result:

                for data in patients_data:

                    if patient["name"] == data["name"]:

                        for time in appointment_times:

                            if time not in used:

                                if data["start"] <= time < data["end"]:

                                    patient["time"] = time
                                    used.append(time)
                                    break
            return render_template("results.html", result=result)
    return render_template("final.html")
if __name__ == "__main__":
    app.run(debug=True, use_reloader=False)