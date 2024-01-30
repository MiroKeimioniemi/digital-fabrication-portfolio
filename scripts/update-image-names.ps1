# Define the directory to search
$dirPath = './content/post'

# Define the extensions to replace
$extensions = @('.png', '.jpg', '.jpeg')

# Get all markdown files in the directory
$files = Get-ChildItem -Path $dirPath -Filter *.md -Recurse

# Process each file
foreach ($file in $files) {
    # Read the file content
    $content = Get-Content -Path $file.FullName -Raw

    # Find all image links
    $imageMatches = [regex]::Matches($content, '!\[.*?\]\((.*?)\)')

    # Process each match
    foreach ($match in $imageMatches) {
        # Only process links with the specified extensions
        if ($extensions -contains [System.IO.Path]::GetExtension($match.Groups[1].Value)) {
            # Replace the extension
            $newMatch = $match.Groups[1].Value -replace '\.png|\.jpeg|\.jpg', '.webp'
            # Update the content
            $content = $content -replace [regex]::Escape($match.Groups[1].Value), $newMatch
        }
    }

    # Find all front matter images
    $frontMatterMatches = [regex]::Matches($content, 'image = "(.*?)"')

    # Process each match
    foreach ($match in $frontMatterMatches) {
        # Only process links with the specified extensions
        if ($extensions -contains [System.IO.Path]::GetExtension($match.Groups[1].Value)) {
            # Replace the extension
            $newMatch = $match.Groups[1].Value -replace '\.png|\.jpeg|\.jpg', '.webp'
            # Update the content
            $content = $content -replace [regex]::Escape($match.Groups[1].Value), $newMatch
        }
    }

    # Write the updated content back to the file
    Set-Content -Path $file.FullName -Value $content
}