import asyncio
import websockets
import os

# Dirección WebSocket del servidor
WS_SERVER = "ws://192.168.4.1/ws"

async def send_message(websocket, message):
    """Envía un mensaje y espera la respuesta."""
    await websocket.send(message)
    print(f"> {message}")

    # Espera la respuesta
    response = await websocket.recv()
    print(f"< {response}")

async def upload_folder(websocket, folder_path):
    """Sube todos los archivos de una carpeta al WebSocket."""
    try:
        # Lista todos los archivos en el directorio especificado
        files = [f for f in os.listdir(folder_path) if os.path.isfile(os.path.join(folder_path, f))]

        # Itera sobre cada archivo y envía el contenido
        for filename in files:
            filepath = os.path.join(folder_path, filename)
            
            # Lee el contenido del archivo
            with open(filepath, 'r') as file:
                content = file.read()

            # Prepara y envía el comando para eliminar el archivo existente
            remove_command = f'remove {filename}'
            await send_message(websocket, remove_command)

            # Prepara y envía el comando para escribir el archivo
            write_command = f'write {filename} "{content}"'
            await send_message(websocket, write_command)
    
    except FileNotFoundError:
        print(f"El directorio {folder_path} no existe.")
    except Exception as e:
        print(f"Error al enviar archivos: {e}")

async def console():
    """Inicia una consola interactiva para enviar comandos y subir archivos de carpetas."""
    async with websockets.connect(WS_SERVER) as websocket:
        print("Conectado a WifiDuck. Escribe tus comandos:")
        
        # Consola interactiva para enviar comandos
        while True:
            command = input(">> ")

            if command.lower() == "exit":
                print("Cerrando la conexión...")
                break
            elif command.startswith("upload"):
                # Verifica si el usuario incluyó la carpeta
                parts = command.split(" ", 1)
                if len(parts) > 1:
                    folder_path = parts[1].strip()
                else:
                    # Solicita la carpeta si no fue especificada
                    folder_path = input("Introduce la carpeta a subir: ").strip()
                
                await upload_folder(websocket, folder_path)
            else:
                # Envía el comando escrito por el usuario
                await send_message(websocket, command)

# Ejecuta la consola
asyncio.run(console())
