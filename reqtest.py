import requests
URL = 'http://localhost/ticket/in.php'
#URL = 'http://localhost/ticket/out.php'

#URL = 'http://58.76.187.204/ticket/out.php'

data = {'MACHINE_KEY': '88756FFQM52'}
response = requests.post(URL, data=data)

#response.status_code
#response.text

