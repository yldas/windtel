from flask import Flask
from flask_cors import CORS

#Activate
app = Flask(__name__)
CORS(app)

# Default route
@app.route('/')
def greeting():
    return 'This is the opening page of the WindTel application'

if __name__ == '__main__':
    app.run(debug=True)