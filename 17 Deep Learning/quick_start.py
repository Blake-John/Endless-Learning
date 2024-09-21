import torch
import matplotlib.pyplot as plt

x = torch.unsqueeze (torch.linspace (-5, 5, 100), dim=1)
y = torch.pow (x, 2) + 3 * torch.rand (x.size ())


class net (torch.nn.Module) :
    def __init__ (self) -> None:
        super(net, self).__init__()
        self.hidden = torch.nn.Linear (1, 5)
        self.out = torch.nn.Linear (5, 1)
        
   
    def forward (self, x) : 
        x = torch.nn.functional.relu (self.hidden (x))
        out = self.out (x)
        return out
    
network = net ()

optimizer = torch.optim.SGD (network.parameters (), lr=0.005)
loss_func = torch.nn.MSELoss ()

plt.ion ()
plt.show ()

for epoch in range (5000) :
    pred = network (x)
    loss = loss_func (pred, y)
    optimizer.zero_grad ()
    loss.backward ()
    optimizer.step ()
    
    if epoch % 5 == 0 :
        plt.cla ()
        plt.scatter (x.data.numpy (), y.data.numpy ())
        plt.plot (x.data.numpy (), pred.data.numpy (), color="green")
        plt.text (3, 0, "Loss : %.4f" % loss.data)
        plt.pause (0.001)
        
plt.ioff ()
plt.show ()

