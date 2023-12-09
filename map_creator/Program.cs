using System.Drawing;
using System.Runtime.Versioning;
using System.Text;

[SupportedOSPlatform("windows")]
public class Program
{
    public static void Main()
    {
        if (!Directory.Exists("maps"))
            return;

        var imgs = new Dictionary<string, Bitmap>();

        foreach (var file in Directory.GetFiles("maps"))
        {
            if (file.Contains(".png"))
            {
                imgs.Add(file.Replace("maps\\", string.Empty).Replace(".png", string.Empty), (Bitmap)Image.FromFile(file));
            }
        }

        var maps = new Dictionary<string, string>();

        foreach (var img in imgs)
        {
            var map_data = new StringBuilder();
            map_data.Append("{\n");
            
            for (int y = 0; y < 18; y++)
            {
                map_data.Append("\t{ ");
                for (int x = 0; x < 80; x++)
                {
                    var pixel = img.Value.GetPixel(x, y);

                    if (pixel.R == 0 && pixel.G == 255 && pixel.B == 0)
                    {
                        map_data.Append('1'); // 1 for tree
                    }
                    else if (pixel.R == 0 && pixel.G == 255 && pixel.B == 255) {
                        map_data.Append('2'); // 2 for water
                    }
                    else if (pixel.R == 255 && pixel.G == 255 && pixel.B == 0) {
                        map_data.Append('3'); // 3 for dirt/rock
                    }
                    else if (pixel.R == 0 && pixel.G == 0 && pixel.B == 0 && pixel.A == 255) {
                        map_data.Append('4'); // 4 for entrance/exit ??
                    }
                    else if (pixel.R == 255 && pixel.G == 255 && pixel.B == 255) {
                        map_data.Append("100"); // 100 for player spawn
                    }
                    else
                    {
                        map_data.Append('0');
                    }

                    if (x < 79)
                        map_data.Append(", ");
                }
                map_data.Append("},\n");
            }

            map_data.Append("};\n");

            File.WriteAllText($"maps/{img.Key}.txt", map_data.ToString());
        }
    }
}