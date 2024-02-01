# Define the directory containing the images
$ImageDir = '.\content'

# Get all image files in the directory and its subdirectories
$ImageFiles = Get-ChildItem -Path $ImageDir -Recurse -Include *.jpg,*.jpeg,*.png

# Loop through each image file
foreach ($ImageFile in $ImageFiles) {
    # Define the output file name
    $OutputFile = $ImageFile.FullName -replace '\.[^.]*$', '.webp'
    
    # Define the ImageMagick command to run on the current image for lossless compression
    $ImageMagickCommandLossless = "magick convert `"$ImageFile`" -strip -adaptive-resize 1200x1920 -define webp:lossless=true `"$OutputFile`""
    
    # Run the ImageMagick command on the file for lossless compression
    Invoke-Expression -Command $ImageMagickCommandLossless

    # Check the file size of the output file
    $OutputFileSize = (Get-Item $OutputFile).Length / 1KB

    # If the file size is larger than 100KB, compress it lossily
    if ($OutputFileSize -gt 100) {
        $ImageMagickCommandLossy = "magick convert `"$ImageFile`" -strip -adaptive-resize 1200x1920 -define webp:lossless=false -quality 85 -define webp:alpha-quality=80 -define webp:auto-filter=true -define webp:method=6 `"$OutputFile`""
        Invoke-Expression -Command $ImageMagickCommandLossy
    }

    # Delete the original image
    Remove-Item -Path $ImageFile.FullName
}