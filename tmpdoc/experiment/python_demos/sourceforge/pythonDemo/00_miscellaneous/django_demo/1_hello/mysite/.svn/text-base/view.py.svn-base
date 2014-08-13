import datetime
from django.http import HttpResponse

def myHello(request):
    return HttpResponse("My Hello World")

def showTime(request):
    now = datetime.datetime.now()
    html = "<html><body>The time now is: %s</body></html>" %now
    return HttpResponse(html)

def showArg(request,arg):
    html = "<html><body>The argument is: %s</body></html>" %arg
    return HttpResponse(html)
