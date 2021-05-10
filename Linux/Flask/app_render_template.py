#-*- coding:utf-8 -*-
# 모듈 로딩 ------------------------
from flask import Flask, render_template

# Flask 객체 생성
# __name__ => python file name
app = Flask(__name__)


# http://localhost:5000/ -----------------------------------------------
@app.route("/")
def helloworld():
    #return "<HTML><BODY bgcolor='yellow'><H1>HELLO WORLD!</H1></BODY></HTML>"
    return render_template("helloworld.html") # HTML 파일을 rendering해주는 함수
    # /templates 디렉토리에 있는 HTML 파일이름을 적어준다. 

# http://localhost:5000/<user> -----------------------------------------
@app.route("/<user>")
def hello_user(user):
    #return "<HTML><BODY bgcolor='pink'><H1>HELLO user</H1></BODY></HTML>"
    return render_template("user.html", name=user) # HTML에 있는 {{name}}에 user가 들어감.
    
    

# python 파일이 실행되는 경우 if문 아래 코드 실행
if __name__ == '__main__':
    # Flask Server Run
    app.run(host="0.0.0.0")
    exit(0)
