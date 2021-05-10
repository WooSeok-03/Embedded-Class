#-*- coding:utf-8 -*-
# 모듈 로딩 ------------------------
from flask import Flask, render_template, request

# Flask 객체 생성
# __name__ => python file name
app = Flask(__name__)


# http://localhost:5000/test -------------------------------------------
@app.route("/")
def test():
    return render_template("post.html")

# http://localhost:5000/post -------------------------------------------
@app.route('/post', methods=['POST'])
def post():
    # HTML 코드에서 test라는 영역의 값을 읽어오기
    value = request.form['test']
    print(value)
    #return value
    return render_template('post.html')

# python 파일이 실행되는 경우 if문 아래 코드 실행
if __name__ == '__main__':
    # Flask Server Run
    app.run(host="0.0.0.0")
    exit(0)
