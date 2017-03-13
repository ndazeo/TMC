# Taller de Matemática Computacional

## Compilar el código pelota.cc

```bash
>> mkoctfile -llibfltk pelota.cc
```

## Ejecutar pelota
```bash
>> function y = f(t) # Creamos una función para la posición y de la pelota
  y = t - floor(t)
endfunction
>> pelota(@f) # Ejecutamos el programa pelota con la función creada
```
