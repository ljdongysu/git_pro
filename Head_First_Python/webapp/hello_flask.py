from flask import Flask

app = Flask(__name__)
@app.route('/')
def hello() -> str:
    return 'Helolo world from Flask!'

app.run()