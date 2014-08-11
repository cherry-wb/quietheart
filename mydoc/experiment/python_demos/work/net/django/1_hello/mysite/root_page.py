from django.http import HttpResponse

def rootPageTip(request):
    return HttpResponse("My Root Page")
