# Define the directory containing the images
$ImageDir = '.\content\post'

# Get all image files in the directory and its subdirectories
$ImageFiles = Get-ChildItem -Path $ImageDir -Recurse -Include *.jpg,*.jpeg,*.png

# Loop through each image file
foreach ($ImageFile in $ImageFiles) {
    # Define the output file name
    $OutputFile = $ImageFile.FullName -replace '\.[^.]*$', '.webp'
    
    # Define the ImageMagick command to run on the current image
    $ImageMagickCommand = "magick convert `"$ImageFile`" -strip -resize 1280x1920 -define webp:lossless=false -quality 75 -define webp:alpha-quality=80 -define webp:auto-filter=true -define webp:method=6 `"$OutputFile`""
    
    # Run the ImageMagick command on the file
    Invoke-Expression -Command $ImageMagickCommand

    # Delete the original image
    Remove-Item -Path $ImageFile.FullName
}