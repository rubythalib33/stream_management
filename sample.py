import base64
import cv2
import json
import time
import numpy as np
from threading import Thread

import websocket

def send_request(ws, command, id, url_path=None):
    request = {"command": command, "id": id}
    if url_path:
        request["url_path"] = url_path
    try:
        ws.send(json.dumps(request))
    except websocket.WebSocketConnectionClosedException as e:
        print("WebSocket connection closed while sending a request:", e)

def on_message(ws, message):
    img_bytes = base64.b64decode(message)
    np_arr = np.frombuffer(img_bytes, np.uint8)
    img = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)

    cv2.imshow("Camera Stream", img)
    cv2.waitKey(1)

def main():
    ws = websocket.WebSocketApp("ws://localhost:9002",
                                 on_message=on_message)

    def run_websocket():
        ws.run_forever()

    websocket_thread = Thread(target=run_websocket)
    websocket_thread.start()

    time.sleep(1)  # Wait for the server to be ready

    send_request(ws, "create_camera", 1, "/app/sample_video/cars.mp4")
    time.sleep(1)  # Wait for the server to create the camera

    while True:
        try:
            send_request(ws, "retrieve_stream", 1)
            time.sleep(0.03)
        except KeyboardInterrupt:
            break

    send_request(ws, "delete_camera", 1)
    time.sleep(1)  # Wait for the server to delete the camera

    ws.close()

if __name__ == "__main__":
    main()
