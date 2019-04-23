import plotly
import plotly.graph_objs as go

axis = ["./fractal 512 32", "./fractal 512 64", "./fractal 1024 32",
        "./fractal 1024 64", "./fractal 2048 128"]
tempoSeq = [9.6992, 18.6922, 38.8286, 74.4327]
statict2c1 = [5.0399, 9.5632, 20.0668, 39.0689]
statict2c4 = [5.0689, 9.5658, 19.9790, 39.3625]
statict4c1 = [3.6067, 6.6445, 14.1861, 27.6467]
statict4c4 = [3.4849, 6.9141, 14.1200, 27.7393]
statict8c1 = [3.5592, 7.0768, 14.2806, 27.6223]
statict8c4 = [3.4840, 7.0485, 14.4311, 27.9940]

dynamict2c1 = [5.0224, 9.5650, 19.9709, 39.5586]
dynamict2c4 = [5.0022, 9.5711, 19.9893, 39.1135]
dynamict4c1 = [3.0740, 6.4418, 13.3130, 25.6992]
dynamict4c4 = [3.4525, 6.4480, 13.3504, 25.7511]
dynamict8c1 = [3.1042, 6.2299, 13.4622, 25.7353]
dynamict8c4 = [3.1713, 6.3888, 13.5444, 25.4934]

guidedt2c1 = [5.1049, 9.7953, 20.4093, 39.1522]
guidedt2c4 = [5.1040, 9.8084, 20.4029, 39.1500]
guidedt4c1 = [3.5228, 6.1861, 13.2940, 25.2587]
guidedt4c4 = [3.3287, 6.1746, 13.5672, 26.3392]
guidedt8c1 = [3.1734, 6.3755, 13.5020, 26.2121]
guidedt8c4 = [3.5474, 6.4783, 13.5793, 26.0182]


v2statict2c1 = [5.0208, 9.6113, 20.0574, 38.5618]
v2statict2c4 = [5.0455, 9.6537, 20.1025, 38.6355]
v2statict4c1 = [3.3938, 6.5740, 14.0115, 27.3451]
v2statict4c4 = [3.7460, 6.8094, 14.5120, 28.3196]
v2statict8c1 = [4.3397, 8.3342, 16.4181, 32.0058]
v2statict8c4 = [4.3088, 8.2871, 16.4781, 31.7219]

v2dynamict2c1 = [5.2306, 10.0374, 20.8821, 40.0541]
v2dynamict2c4 = [5.0941, 9.7530, 20.2794, 38.8343]
v2dynamict4c1 = [3.6172, 6.2748, 13.5719, 26.8245]
v2dynamict4c4 = [3.1328, 6.0163, 13.7936, 25.2812]
v2dynamict8c1 = [3.7974, 7.1651, 14.5595, 28.4982]
v2dynamict8c4 = [3.3989, 6.7769, 14.0891, 27.0655]

v2guidedt2c1 = [5.5302, 11.2488, 22.0801, 44.9454]
v2guidedt2c4 = [5.5411, 11.2601, 22.0944, 44.9461]
v2guidedt4c1 = [3.4302, 6.6560, 13.8331, 27.8531]
v2guidedt4c4 = [3.3344, 6.8658, 14.5059, 29.1013]
v2guidedt8c1 = [3.4013, 6.7341, 14.0851, 27.0954]
v2guidedt8c4 = [3.7544, 6.8058, 13.9834, 26.5010]

trace1 = go.Bar(
    x=axis,
    y=tempoSeq,
    text=tempoSeq,
    textposition='auto',
    name='Serial',
)

trace2 = go.Bar(
    x=axis,
    y=statict2c1,
    text=statict2c1,
    textposition='auto',
    name='Static Thread=2 Chunk=1 ',
)

trace3 = go.Bar(
    x=axis,
    y=statict2c4,
    text=statict2c4,
    textposition='auto',
    name='Static Thread=2 Chunk=4 ',
)
trace4 = go.Bar(
    x=axis,
    y=statict4c1,
    text=statict4c1,
    textposition='auto',
    name='Static Thread=4 Chunk=1 ',
)
trace5 = go.Bar(
    x=axis,
    y=statict4c4,
    text=statict4c4,
    textposition='auto',
    name='Static Thread=4 Chunk=4 ',
)
trace6 = go.Bar(
    x=axis,
    y=statict8c1,
    text=statict8c1,
    textposition='auto',
    name='Static Thread=8 Chunk=1 ',
)
trace7 = go.Bar(
    x=axis,
    y=statict8c4,
    text=statict8c4,
    textposition='auto',
    name='Static Thread=8 Chunk=4 ',
)

trace8 = go.Bar(
    x=axis,
    y=dynamict2c1,
    text=dynamict2c1,
    textposition='auto',
    name='Dynamic Thread=2 Chunk=1 ',
)

trace9 = go.Bar(
    x=axis,
    y=dynamict2c4,
    text=dynamict2c4,
    textposition='auto',
    name='Dynamic Thread=2 Chunk=4 ',
)
trace10 = go.Bar(
    x=axis,
    y=dynamict4c1,
    text=dynamict4c1,
    textposition='auto',
    name='Dynamic Thread=4 Chunk=1 ',
)
trace11 = go.Bar(
    x=axis,
    y=dynamict4c4,
    text=dynamict4c4,
    textposition='auto',
    name='Dynamic Thread=4 Chunk=4 ',
)
trace12 = go.Bar(
    x=axis,
    y=dynamict8c1,
    text=dynamict8c1,
    textposition='auto',
    name='Dynamic Thread=8 Chunk=1 ',
)
trace13 = go.Bar(
    x=axis,
    y=dynamict8c4,
    text=dynamict8c4,
    textposition='auto',
    name='Dynamic Thread=8 Chunk=4 ',
)

trace14 = go.Bar(
    x=axis,
    y=guidedt2c1,
    text=guidedt2c1,
    textposition='auto',
    name='Guided Thread=2 Chunk=1 ',
)

trace15 = go.Bar(
    x=axis,
    y=guidedt2c4,
    text=guidedt2c4,
    textposition='auto',
    name='Guided Thread=2 Chunk=4 ',
)
trace16 = go.Bar(
    x=axis,
    y=guidedt4c1,
    text=guidedt4c1,
    textposition='auto',
    name='Guided Thread=4 Chunk=1 ',
)
trace17 = go.Bar(
    x=axis,
    y=guidedt4c4,
    text=guidedt4c4,
    textposition='auto',
    name='Guided Thread=4 Chunk=4 ',
)
trace18 = go.Bar(
    x=axis,
    y=guidedt8c1,
    text=guidedt8c1,
    textposition='auto',
    name='Guided Thread=8 Chunk=1 ',
)
trace19 = go.Bar(
    x=axis,
    y=guidedt8c4,
    name='Guided Thread=8 Chunk=4 ',
    text=guidedt8c4,
    textposition='auto',
)


trace20 = go.Bar(
    x=axis,
    y=v2statict2c1,
    text=v2statict2c1,
    textposition='auto',
    name='v2 Static Thread=2 Chunk=1 ',
)

trace21 = go.Bar(
    x=axis,
    y=v2statict2c4,
    text=v2statict2c4,
    textposition='auto',
    name='v2Static Thread=2 Chunk=4 ',
)
trace22 = go.Bar(
    x=axis,
    y=v2statict4c1,
    text=v2statict4c1,
    textposition='auto',
    name='v2Static Thread=4 Chunk=1 ',
)
trace23 = go.Bar(
    x=axis,
    y=v2statict4c4,
    text=v2statict4c4,
    textposition='auto',
    name='v2Static Thread=4 Chunk=4 ',
)
trace24 = go.Bar(
    x=axis,
    y=v2statict8c1,
    text=v2statict8c1,
    textposition='auto',
    name='v2Static Thread=8 Chunk=1 ',
)
trace25 = go.Bar(
    x=axis,
    y=v2statict8c4,
    text=v2statict8c4,
    textposition='auto',
    name='v2Static Thread=8 Chunk=4 ',
)

trace26 = go.Bar(
    x=axis,
    y=v2dynamict2c1,
    text=v2dynamict2c1,
    textposition='auto',
    name='v2Dynamic Thread=2 Chunk=1 ',
)

trace27 = go.Bar(
    x=axis,
    y=v2dynamict2c4,
    text=v2dynamict2c4,
    textposition='auto',
    name='v2Dynamic Thread=2 Chunk=4 ',
)
trace28 = go.Bar(
    x=axis,
    y=v2dynamict4c1,
    text=v2dynamict4c1,
    textposition='auto',
    name='v2Dynamic Thread=4 Chunk=1 ',
)
trace29 = go.Bar(
    x=axis,
    y=v2dynamict4c4,
    text=v2dynamict4c4,
    textposition='auto',
    name='v2Dynamic Thread=4 Chunk=4 ',
)
trace30 = go.Bar(
    x=axis,
    y=v2dynamict8c1,
    text=v2dynamict8c1,
    textposition='auto',
    name='v2Dynamic Thread=8 Chunk=1 ',
)
trace31 = go.Bar(
    x=axis,
    y=v2dynamict8c4,
    text=v2dynamict8c4,
    textposition='auto',
    name='v2Dynamic Thread=8 Chunk=4 ',
)

trace32 = go.Bar(
    x=axis,
    y=v2guidedt2c1,
    text=v2guidedt2c1,
    textposition='auto',
    name='v2Guided Thread=2 Chunk=1 ',
)

trace33 = go.Bar(
    x=axis,
    y=v2guidedt2c4,
    text=v2guidedt2c4,
    textposition='auto',
    name='v2Guided Thread=2 Chunk=4 ',
)
trace34 = go.Bar(
    x=axis,
    y=v2guidedt4c1,
    text=v2guidedt4c1,
    textposition='auto',
    name='v2Guided Thread=4 Chunk=1 ',
)
trace35 = go.Bar(
    x=axis,
    y=v2guidedt4c4,
    text=v2guidedt4c4,
    textposition='auto',
    name='v2Guided Thread=4 Chunk=4 ',
)
trace36 = go.Bar(
    x=axis,
    y=v2guidedt8c1,
    text=v2guidedt8c1,
    textposition='auto',
    name='v2Guided Thread=8 Chunk=1 ',
)
trace37 = go.Bar(
    x=axis,
    y=v2guidedt8c4,
    name='v2Guided Thread=8 Chunk=4 ',
    text=v2guidedt8c4,
    textposition='auto',
)
data = [trace1, trace2, trace3, trace4, trace5, trace6, trace7,
        trace8, trace9, trace10, trace11, trace12, trace13,
        trace14, trace15, trace16, trace17, trace18, trace19, trace20,
        trace21, trace22, trace23, trace24, trace25, trace26, trace27, trace28,
        trace29, trace30, trace31, trace32, trace33, trace34, trace35, trace36, trace37]
layout = go.Layout(
    barmode='group'
)

plotly.offline.plot(data, filename='grouped-bar-direct-labels')
