import os
from os.path import join, isdir
from mdutils.mdutils import MdUtils
from mdutils import Html

mdFile = MdUtils(file_name='Homework_2_Report', title='Report of Data-Level fusion homework')

mdFile.new_header(level=1, title='Overview')  # style is set 'atx' format by default.

mdFile.new_paragraph("This file consists of the evaluation report for the Data-level fusion homework. 12 pairs of " 
                        "half-sized images have been taken from the 2006 Stereo Dataset and tested.")
mdFile.new_paragraph("This report will look into the each pair of images and output the following:")
mdFile.new_line("  - Output of the upsampling algorithm")
mdFile.new_line("  - Table with the metrics resulted from the comparison of the `Ground Truth` with the `Bilateral Filter` output as well as the processing time")
mdFile.new_line("  - Best image and the sigma choice for each metric tested.")
mdFile.new_paragraph()


data_path = "./data/"

dir_list = [join(data_path,f) for f in os.listdir(data_path) if isdir(os.path.join(data_path, f))]
eval_path = [f+"/eval/" for f in dir_list ]


mdFile.new_header(level=1, title='Directories tested')

for directory in eval_path:
    dir_name =  directory.split("/")[2]
    mdFile.new_header(level=2, title=dir_name)

    # Upsampling result
    mdFile.new_header(level=3, title="Upsampling result")
    upsampling_image_path = directory + 'upsampled_image.png'
    mdFile.new_line(Html.image(path=upsampling_image_path, size='300x300', align='center'))
    mdFile.new_paragraph()

    # Parse eval file (load it)
    mdFile.new_header(level=3, title="Resulted metrics")

    eval_file_path = directory + "eval_results.txt"
    list_of_items = []
    with open(eval_file_path, 'r') as f:

        # Table header
        list_of_items = ["File Name", "Spatial Sigma", "Spectral Sigma", "Time(MS)", "SSD", "RMSE", "PSNR", "SSIM"]
        sp_sigma = []; spec_sigma = []; time_list = []; ssd_list = []; rmse_list = []; psnr_list = []; ssim_list = []

        while True:
            line = f.readline().strip()
            line = line.split(',')
            if len(line) < 16 or not line:
                break
            file_name = line[0]
            spatial_sigma = float(line[2])
            spectral_sigma = float(line[4])
            time_ms = float(line[6])
            ssd = float(line[9])
            rmse = line[11]
            psnr = line[13]
            ssim = line[15]
            list_of_items.extend([file_name, spatial_sigma, spectral_sigma, time_ms, ssd, rmse, psnr, ssim])

            # Store the images that are have the best metrics
            sp_sigma.append(spatial_sigma); spec_sigma.append(spectral_sigma)
            time_list.append(time_ms); ssd_list.append(ssd); rmse_list.append(rmse)
            psnr_list.append(psnr); ssim_list.append(ssim)

    
        mdFile.new_line()
        mdFile.new_table(columns=8, rows=17, text=list_of_items, text_align='center')

        # Best Time
        best_time_image = time_list.index(min(time_list))
        mdFile.new_header(level=3, title="Best processing time")
        mdFile.new_paragraph(f"Spatial Sigma: {sp_sigma[int(best_time_image)]} . Spectral Sigma: {spec_sigma[int(best_time_image)]}")
        time_image_path = directory + str(best_time_image) + '.png'
        mdFile.new_line(Html.image(path=time_image_path, size='300x300', align='center'))
        mdFile.new_paragraph()

        # Best SSD
        best_ssd_image = ssd_list.index(min(ssd_list))
        mdFile.new_header(level=3, title="Best SSD value")
        mdFile.new_paragraph(f"Spatial Sigma: {sp_sigma[int(best_ssd_image)]} . Spectral Sigma: {spec_sigma[int(best_ssd_image)]}")
        ssd_image_path = directory + str(best_ssd_image) + '.png'
        mdFile.new_line(Html.image(path=ssd_image_path, size='300x300', align='center'))
        mdFile.new_paragraph()

        # Best RMSE
        best_rmse_image = rmse_list.index(min(rmse_list))
        mdFile.new_header(level=3, title="Best RMSE value")
        mdFile.new_paragraph(f"Spatial Sigma: {sp_sigma[int(best_rmse_image)]} . Spectral Sigma: {spec_sigma[int(best_rmse_image)]}")
        rmse_image_path = directory + str(best_rmse_image) + '.png'
        mdFile.new_line(Html.image(path=rmse_image_path, size='300x300', align='center'))
        mdFile.new_paragraph()

        # Best PSNR
        best_psnr_image = psnr_list.index(max(psnr_list))
        mdFile.new_header(level=3, title="Best PSNR value")
        mdFile.new_paragraph(f"Spatial Sigma: {sp_sigma[int(best_psnr_image)]} . Spectral Sigma: {spec_sigma[int(best_psnr_image)]}")
        psnr_image_path = directory + str(best_psnr_image) + '.png'
        mdFile.new_line(Html.image(path=psnr_image_path, size='300x300', align='center'))
        mdFile.new_paragraph()

        # Best SSIM
        best_ssim_image = ssim_list.index(max(ssim_list))
        mdFile.new_header(level=3, title="Best SSIM value")
        mdFile.new_paragraph(f"Spatial Sigma: {sp_sigma[int(best_ssim_image)]} . Spectral Sigma: {spec_sigma[int(best_ssim_image)]}")
        ssim_image_path = directory + str(best_ssim_image) + '.png'
        mdFile.new_line(Html.image(path=ssim_image_path, size='300x300', align='center'))
        mdFile.new_paragraph()

# Create a table of contents
mdFile.new_table_of_contents(table_title='Contents', depth=2)
mdFile.create_md_file()




