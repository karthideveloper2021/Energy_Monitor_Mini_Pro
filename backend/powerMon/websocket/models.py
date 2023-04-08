from django.db import models

# Create your models here.

class Client(models.Model):
    id=models.CharField(max_length=10,primary_key=True)
    created=models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.id