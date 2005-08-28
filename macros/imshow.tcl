
set w .imshow
catch {destroy $w}
toplevel $w

wm title $w "image show"
wm iconname $w "imshow"

frame $w.top -borderwidth 10
pack $w.top 

#Zoom In button
button $w.top.zoomin -text "Zoom In" -command {zoom_in}
pack $w.top.zoomin -side left

#Zoom Out button
button $w.top.zoomout -text "Zoom Out" -command {zoom_out}
pack $w.top.zoomout -side left

#close button
button $w.top.exit -text Close -command {destroy .imshow}
pack $w.top.exit -side right




#create image	
image create photo tkimage 
tkimage put  $imagedata

#create a scrollable canvas
canvas $w.can 
pack $w.can -expand 1 -fill both
$w.can create image 0 0 -tags item -image tkimage  -anchor nw

$w.can configure -scrollregion [$w.can bbox all]

set zoomscale 1.0

proc zoom_out {} {
    global w tkimage zoomscale
    if ($zoomscale>=8.0) {
	set zoomscale 8.0
	return
    }
    set zoomscale [expr {$zoomscale*2} ]

    $w.can delete item 
    catch {image delete zoomimage}
    image create photo zoomimage
    zoomimage blank
    if ($zoomscale>=1.0) {
	zoomimage copy tkimage -zoom [format "%.0f" $zoomscale]
    } else {
	zoomimage copy tkimage -subsample [format "%.0f" [expr {1/$zoomscale}]]
    }
    $w.can create image 0 0 -tags item -image zoomimage  -anchor nw
} 

proc zoom_in {} {
    global w tkimage zoomscale
    if ($zoomscale<=0.125) {
	set zoomscale 0.125
	return
    }
    set zoomscale [expr {$zoomscale/2.0} ]

    $w.can delete item 
    catch {image delete zoomimage}
    image create photo zoomimage
    zoomimage blank
    if ($zoomscale>=1) {
	zoomimage copy tkimage -zoom [format "%.0f" $zoomscale]
    } else {
	zoomimage copy tkimage -subsample [format "%.0f" [expr {1/$zoomscale}]]
    }
    $w.can create image 0 0 -tags item -image zoomimage  -anchor nw
} 




