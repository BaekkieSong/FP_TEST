from flask import Flask, send_file, request, render_template, jsonify
import os

def assure_mkdirs(target):
  if not os.path.exists(target):
    os.makedirs(target)

DIR = 'package/win/installer/x64/'
UPLOAD_DIR = os.path.normpath(os.path.join(os.path.dirname(__file__),DIR))
#assure_mkdirs(UPLOAD_DIR)

# 1GB limit per file
MAX_CONTENT_LENGTH = 1024 * 1024 * 1000

app = Flask(__name__)
app.config['UPLOAD_DIR'] = UPLOAD_DIR
app.config['MAX_CONTENT_LENGTH'] = MAX_CONTENT_LENGTH
app.config['ALLOWED_EXTENSIONS'] = ['png', 'gif', 'jpeg', 'txt', 'jpg', 'dll', 'exe']

def need_version_upgrade(request):
  dirnames = os.listdir(UPLOAD_DIR)
  is_new_version = False
  new_version_name = ""
  print ("client_version: " + request.headers['version'])
  for version_name in dirnames:
    version_num = version_name.replace('v','')
    print ("version: " + version_num)
    server_versions = version_num.split('.')
    client_versions = request.headers['version'].split('.')
    if (len(server_versions) == len(client_versions)):
      for i in range(len(server_versions)):
        if server_versions[i] > client_versions[i]:
          print ("server_new_version: " + version_name)
          is_new_version = True
          new_version_name = version_name
          break
        elif server_versions[i] < client_versions[i]:
          break
  return [is_new_version, version_name]

def allowed_file(filename):
  print (os.path.splitext(filename)[1])
  return '.' in filename and filename.rsplit('.', 1)[1].lower() in app.config['ALLOWED_EXTENSIONS']

@app.route('/upload', methods=['POST'])
def upload_file():
  target_dir = os.path.join(app.config['UPLOAD_DIR'], 'v' + request.headers['version'])
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
  results = need_version_upgrade(request)
  if results[0] == True:
    target = os.path.join(app.config['UPLOAD_DIR'], str(results[1]), request.headers['file'])

    if(os.path.exists(target)):
      return send_file(target, as_attachment=True)
  return jsonify(download='failed', cause='file not founded')

if __name__ == '__main__':
  app.run(host='0.0.0.0', port=3000)

