import torch
import os
from PIL import Image, ImageDraw
from torchvision.transforms import functional as F

# Chemin vers le modèle YOLOv8
model_path = "C:/Users/Dell/Desktop/stage/model_- 3 august 2023 15_52.pt"

# Chemin vers le répertoire contenant les images à traiter
image_dir = "C:/Users/Dell/Desktop/stage/NEWDATA"

# Chemin vers le répertoire où enregistrer les images traitées
output_dir = "C:/Users/Dell/Desktop/stage/saveee"

# Charger le modèle YOLOv8
model = torch.load(model_path)
model.eval()

# Liste des classes (labels) détectables par le modèle
classes = ["okgauche", "okdroite", "nokdroite","nokgauche"]  # Remplacez par vos classes réelles

# Parcourir les images dans le répertoire
for image_name in os.listdir(image_dir):
    if image_name.endswith((".jpg", ".png", ".jpeg")):
        image_path = os.path.join(image_dir, image_name)
        output_path = os.path.join(output_dir, image_name)

        # Charger l'image
        image = Image.open(image_path).convert("RGB")

        # Prétraitement de l'image pour l'entrée du modèle
        image_tensor = F.to_tensor(image).unsqueeze(0)

        # Faire la prédiction avec le modèle
        with torch.no_grad():
            detections = model(image_tensor)

        # Traiter les résultats de la détection
        if detections is not None:
            for detection in detections[0]:
                class_id = int(detection[5])
                label = classes[class_id]
                confidence = detection[4]
                bbox = detection[:4] * torch.tensor([image.width, image.height, image.width, image.height])

                # Dessiner la boîte englobante et l'étiquette sur l'image
                draw = ImageDraw.Draw(image)
                draw.rectangle(xy=bbox.tolist(), outline="red", width=2)
                draw.text((bbox[0], bbox[1]), f"{label}: {confidence:.2f}", fill="red")

        # Enregistrer l'image traitée avec les annotations
        image.save(output_path)

print("Terminé!")
