# Guía Rápida para conexión Github
>Sirve para conectarse a una PC ajena de forma muy rapida y poder actualizar repositorios

**Requisitos:** Estar logueado previamente desde el celular en la app de Github

1. Abrir la terminal y escribir:

    ```bash
    gh auth login
    ```

2. Responder las preguntas:

    * **What is your preferred protocol for Git operations?** Seleccioná HTTPS

    * **Authenticate Git with your GitHub credentials?** Seleccioná Yes

    * **How would you like to authenticate GitHub CLI?** Seleccioná Login with a web browser

3. Proceso de Login:

    * La terminal te va a mostrar un código de 8 dígitos (ejemplo: ABCD-1234) y que presiones enter para ir a loguearte

    * Usar el Celular para 2FA y entrar.

4. Para salir sin problemas:

    ```bash
    gh auth logout
    ```
    Le das que sí (Y) y desvinculás la máquina en 2 segundos. ¡Con eso estás 100% cubierto!

## Manual de Uso de gh

### Ver tus repositorios
Para ver la lista de todos tus repositorios:

```bash
gh repo list
```

### Clonar el repositorio en el que vas a trabajar:

No hace falta que copies enlaces HTTPS o SSH largos. Con el CLI podés clonarlo directamente por su nombre:

```bash
gh repo clone tu-usuario/nombre-del-repo
```

>El manejo de los pull y push es idéntico al git usual.

### Borrá la carpeta del proyecto de la PC del laboratorio:
Regresá a la carpeta superior y borrá la carpeta local:
```bash
cd ..
rm -rf nombre-del-repo
```

