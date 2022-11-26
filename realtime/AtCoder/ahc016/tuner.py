import optuna
import subprocess

case = open('cases/0007.txt', 'r', encoding='UTF-8').read()

def objective(trial):
    start_temperature = trial.suggest_float('start_temperature', 0, 10000)
    end_temperature = trial.suggest_float('end_temperature', 0, start_temperature)
    inpt = case + "\n" + ' '.join((str(start_temperature),str(end_temperature))) + "\n";
    res = subprocess.run(["./solver10.exe"], input=inpt, capture_output=True, text=True)
    return -int(res.stderr)

study = optuna.create_study()
study.optimize(objective, n_trials=100)

print(study.best_trial)
