from django.http import HttpResponse

def home(request):
    return HttpResponse('SCH/S - Scheduler Server')

