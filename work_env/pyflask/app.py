from flask import Flask, send_file, request, render_template, jsonify
import os

def assure_mkdirs(target):
    if not os.path.exists(target):
        os.mkdir(target)

UPLOAD_DIR = 'static/upload/'
assure_mkdirs(UPLOAD_DIR)

# 100MB limit
MAX_CONTENT_LENGTH = 1024 * 1024 * 100

app = Flask(__name__)
app.config['UPLOAD_DIR'] = UPLOAD_DIR
app.config['MAX_CONTENT_LENGTH'] = MAX_CONTENT_LENGTH
app.config['ALLOWED_EXTENSIONS'] = ['png', 'gif', 'jpeg', 'txt', 'jpg', 'dll']

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in app.config['ALLOWED_EXTENSIONS']

@app.route('/upload', methods=['POST'])
def upload_file():
    target_dir = app.config['UPLOAD_DIR'] + 'v' + request.headers['version'] + '/'
    assure_mkdirs(target_dir)
    file = None
    if 'file' in request.files:
        file = request.files['file']
    if file and allowed_file(file.filename):
        file.save(os.path.join(target_dir, file.filename))
        return jsonify(upload='success')
    return jsonify(upload='failed', allowed_extentions=app.config['ALLOWED_EXTENSIONS'])

@app.route('/download', methods = ['GET'])
def download_file():
    target = app.config['UPLOAD_DIR'] + 'v' + request.headers['version'] + "/" + request.headers['file']
    if(os.path.exists(target)):
        return send_file(target, as_attachment=True)
    return jsonify(download='failed', cause='file not founded')

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=3000)

