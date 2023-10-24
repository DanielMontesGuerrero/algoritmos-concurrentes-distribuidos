"""
Alumno: Daniel Montes Guerrero
Ejecutar: python procesos.py
"""
import os

pid = os.fork()

if pid > 0:
    print("Soy el padre", os.getpid())
else:
    print("Soy el hijo", os.getpid(), "con padre", os.getppid())
